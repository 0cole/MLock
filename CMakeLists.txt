# Minimum version required
cmake_minimum_required(VERSION 3.10)

project(MLock VERSION 1.0)

# 2017 C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# OpenSSL installation
find_package(OpenSSL REQUIRED)
if (NOT OpenSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found!")
endif()

#Include Directories
include_directories(${OPENSSL_INCLUDE_DIR})

# Executables
add_executable(MLock
    src/main.cpp
    src/util.cpp
    src/welcome.cpp
    src/generate.cpp
    src/generationConfig.cpp
    src/library.cpp
)

# Include directories
target_include_directories(MLock PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(MLock OpenSSL::SSL OpenSSL::Crypto)
