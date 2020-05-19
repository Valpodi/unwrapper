cmake_minimum_required(VERSION 3.5.1)
project(QuickStart)

SET( CMAKE_CXX_STANDARD 11)

SET(BOOSTROOT /usr/include/boost169)
find_package(Boost 1.69)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(Common)
include_directories(Unwrapper)
include_directories(Logging)

add_executable(Unwrapper
        Unwrapper/Unwrapper.hpp
        Unwrapper/Unwrapper.cpp
        Unwrapper/WrapperInterface.cpp
        Unwrapper/WrapperInterface.hpp
        Unwrapper/UnwrapperMain.cpp
        Unwrapper/CloakedDagger.hpp
        Unwrapper/CloakedDagger.cpp)


target_link_libraries(Unwrapper
        pthread
        )
