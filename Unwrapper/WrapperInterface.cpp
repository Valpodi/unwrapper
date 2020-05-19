#include "ApplicationLog.hpp"
#include "WrapperInterface.hpp"

bool WrapperInterface::checkCrc(const std::string& manifestCrc, const std::string& crcChecksum) const
{
  if (manifestCrc != crcChecksum)
  {
    applicationLog.error("Un/None Wrapper FAILED CRC. Actual: " + crcChecksum + ", manifest: " + manifestCrc);
    return false;
  }

  return true;
}
