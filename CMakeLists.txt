# Minimum version required
cmake_minimum_required(VERSION 3.10)

project(MLock VERSION 1.0)

# 2017 C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Executables
add_executable(MLock
    src/main.cpp
    src/util.cpp
    src/welcome.cpp
)

# Include directories
target_include_directories(MLock PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Potentially find and link openSSL in the future if i choose to
