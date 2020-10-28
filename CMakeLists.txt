cmake_minimum_required(VERSION 3.15)
project(libbase)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program main.cpp semaphore/ZybSemaphore.cpp)
