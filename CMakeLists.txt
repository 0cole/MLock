# Minimum version required
cmake_minimum_required(VERSION 3.10)

project(MLock VERSION 1.0)

# 2017 C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add vcpkg (if someone else cloned this repo, make sure you change the vcpkg path)
set(CMAKE_TOOLCHAIN_FILE "/home/cole/frameworks/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/share" ${CMAKE_PREFIX_PATH})

# OpenSSL installation
find_package(OpenSSL REQUIRED)
if (NOT OpenSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found!")
endif()

# Nlohmann-json installation
find_package(nlohmann_json CONFIG REQUIRED)

#Include Directories
include_directories(${OPENSSL_INCLUDE_DIR})

# Executables
add_executable(MLock
    src/main.cpp
    src/util.cpp
    src/welcome.cpp
    src/generate.cpp
    src/generationConfig.cpp
    src/library/library.cpp
    src/library/add.cpp
    src/library/fetch.cpp
    src/library/remove.cpp
)

# Include directories
target_include_directories(MLock PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(MLock
    PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json
    )
