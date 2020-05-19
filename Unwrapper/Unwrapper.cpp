
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <boost/endian/conversion.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "ApplicationLog.hpp"
#include "StreamingFileInfo.hpp"
#include "Unwrapper.hpp"
#include "CloakedDagger.hpp"

void Unwrapper::unwrapFromStream(std::istream& inputStream, std::ostream& outputStream)
{
  if (isCloakDaggerEncoded(inputStream))
  {
    applicationLog.debug("Unwrapper: detected encoded - decoding...");
    cloakDaggerUnwrap(inputStream, outputStream);
  }
  else
  {

    applicationLog.debug("Unwrapper: not encoded - copying to output...");
    outputStream << inputStream.rdbuf();
  }
}

bool Unwrapper::isCloakDaggerEncoded(std::istream& inputStream) const
{
  return inputStream.peek() == CloakedDagger::cloakedDaggerIdentifierByte;
}

bool Unwrapper::isCloakDaggerEncoded(const BytesBuffer& inputData) const
{
  return inputData.size() != 0 &&
         CloakedDagger::cloakedDaggerIdentifierByte == inputData.at(0);
}


void Unwrapper::cloakDaggerUnwrap(std::istream& inputStream, std::ostream& outputStream) const
{
  const CloakedDagger wrappedHeader(inputStream);

  char readByte;
  uint64_t count = 0;

  while (!inputStream.get(readByte).eof())
    {
      outputStream.put(readByte ^ static_cast<char>(wrappedHeader.key[count % CloakedDagger::maskLength]));
      count++;
    }
}


void Unwrapper::unwrapFromFile(const std::string& wrappedFilePath, const std::string& unwrappedFilePath)
{
  std::ifstream wrappedInputFile(wrappedFilePath, std::ifstream::binary);
  std::ofstream unwrappedOutputFile(unwrappedFilePath, std::ifstream::binary | std::ios::trunc);

  if (!wrappedInputFile.is_open())
  {
    throw std::runtime_error("Could not open file for reading: " + wrappedFilePath);
  }

  if (!unwrappedOutputFile.is_open())
  {
    throw std::runtime_error("Could not open file for writing: " + unwrappedFilePath);
  }

  unwrapFromStream(wrappedInputFile, unwrappedOutputFile);
}

BytesBuffer Unwrapper::unwrap(const BytesBuffer& inputData)
{
  if (!isCloakDaggerEncoded(inputData))
  {
    return inputData;
  }

  const auto wrappedHeader = CloakedDagger::createFromBuffer(inputData);

  uint64_t count = 0;

  BytesBuffer unwrappedBytes;
  unwrappedBytes.reserve(inputData.size() - CloakedDagger::headerSize());

  for (size_t i=CloakedDagger::headerSize(); i<inputData.size(); i++)
  {
    unwrappedBytes.push_back(inputData[i] ^ static_cast<unsigned char>(wrappedHeader.key[count % CloakedDagger::maskLength]));
    count++;
  }

  return unwrappedBytes;
}

StreamingFileInfo Unwrapper::startFile(const StreamingFileInfo& info, const BytesBuffer&)
{
  return info;
}
