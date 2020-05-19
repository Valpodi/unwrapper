#include <iostream>

struct ApplicationLog
{
    void debug(const std::string& message)
    {
        std::cout << message;
    }

    void error(const std::string& message)
    {
        std::cerr << message;
    }
};

extern ApplicationLog applicationLog;
