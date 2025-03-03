cmake_minimum_required(VERSION 3.23)

# Set the project name
project(MJGame)

# Find SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# Add the executable
file(GLOB SOURCES "src/*.cpp")
add_executable(Game ${SOURCES})
target_link_libraries(Game PRIVATE SDL3::SDL3)

# Specify the C/C++ standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)