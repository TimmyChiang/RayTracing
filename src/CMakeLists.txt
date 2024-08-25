cmake_minimum_required(VERSION 3.30.2)

project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(RayTracing main.cc)

target_include_directories(RayTracing PUBLIC ${PROJECT_BINARY_DIR})