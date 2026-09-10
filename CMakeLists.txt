cmake_minimum_required(VERSION 3.20)
project(ThreeDelightLicenseDemo VERSION 1.0 LANGUAGES CXX)

add_executable(license_demo
    src/main.cpp
    src/LicenseServer.cpp
)

target_include_directories(license_demo PRIVATE include)
target_compile_features(license_demo PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(license_demo PRIVATE /W4 /permissive-)
else()
    target_compile_options(license_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

