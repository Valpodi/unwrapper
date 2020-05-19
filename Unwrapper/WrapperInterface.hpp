
#ifndef GATEWAY_WRAPPERINTERFACE_HPP
#define GATEWAY_WRAPPERINTERFACE_HPP

#include <string>
#include "BytesBuffer.hpp"

struct StreamingFileInfo;

class WrapperInterface
{
public:
  virtual ~WrapperInterface() = default;
  virtual BytesBuffer unwrap(const BytesBuffer& data) = 0;
  virtual StreamingFileInfo startFile(const StreamingFileInfo& info, const BytesBuffer& firstData) = 0;
  virtual bool checkCrc(const std::string& manifestCrc, const std::string& crcChecksum) const;
};

#endif //GATEWAY_WRAPPERINTERFACE_HPP
