cmake_minimum_required(VERSION 3.22.1)

# set(CMAKE_CXX_STANDARD 17)
project(CppND-Conversations-in-Elevators)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src

# Add project executable
add_executable(CppND-Conversations-in-Elevators ${project_SRCS})
