#include <ApplicationLog.hpp>
#include <iostream>
#include "Unwrapper.hpp"

ApplicationLog applicationLog;

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    std::cerr << "Not enough arguments. Usage:" << std::endl << argv[0] << " inputfile outputfile" << std::endl;
    exit(1);
  }

  try
  {
    Unwrapper().unwrapFromFile(argv[1], argv[2]);
  }
  catch (const std::exception& e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    exit(2);
  }

  exit(0);
}
