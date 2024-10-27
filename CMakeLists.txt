# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Njordx)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the executable
add_executable(NjordxApp ${SOURCES})

# Add any necessary libraries (e.g., for external dependencies)
# target_link_libraries(NjordxApp library_name)
