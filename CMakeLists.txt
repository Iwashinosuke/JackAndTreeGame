cmake_minimum_required(VERSION 3.20)

# Set the project name
project(JTGame)

# Find SDL3
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# # Set the build target
# set(BUILD_TARGET CACHE STRING "Build target?")

# # Build settings for each target
# if(${BUILD_TARGET} STREQUAL windows)
#     include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PC_WIN.cmake)
# else()
#     include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PC_LINUX.cmake)
# endif()

# Add the executable
file(GLOB SOURCES "src/*.cpp")
add_executable(Game ${SOURCES})
target_link_libraries(Game PRIVATE SDL3::SDL3)
# if(${BUILD_TARGET} STREQUAL windows)
#     target_link_libraries(Game PRIVATE SDL3::SDL3)
# else()
#     target_link_libraries(Game PUBLIC /usr/x86_64-w64-mingw32/lib/libSDL3.dll.a)
# endif()

# Specify the C/C++ standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)