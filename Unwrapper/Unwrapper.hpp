

#ifndef SHIM_UNWRAPPER_HPP
#define SHIM_UNWRAPPER_HPP

#include <string>
#include "WrapperInterface.hpp"

namespace boost {namespace filesystem {class path;}}


class UnwrapperInterface
{
public:
  virtual ~UnwrapperInterface() = default;
  virtual void unwrapFromStream(std::istream& inputStream, std::ostream& outputStream) = 0;
  virtual void unwrapFromFile(const std::string& wrappedFilePath, const std::string& unwrappedFilePath) = 0;
};

class Unwrapper: public UnwrapperInterface, public WrapperInterface
{
public:
  Unwrapper() = default;
  ~Unwrapper() = default;
  void unwrapFromStream(std::istream& inputStream, std::ostream& outputStream) override ;
  void unwrapFromFile(const std::string& wrappedFilePath, const std::string& unwrappedFilePath) override;
  StreamingFileInfo startFile(const StreamingFileInfo& info, const BytesBuffer& firstData) override;
  BytesBuffer unwrap(const BytesBuffer& inputData) override;

private:

  bool isCloakDaggerEncoded(std::istream& inputStream) const;
  bool isCloakDaggerEncoded(const BytesBuffer& inputData) const;
  void cloakDaggerUnwrap(std::istream& inputStream, std::ostream& outputStream) const;
};



#endif //SHIM_UNWRAPPER_HPP
