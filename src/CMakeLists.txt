cmake_minimum_required(VERSION 3.10)

project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(RayTracing main.cc vec3.h color.h ray.h hittable.h 
                sphere.h hittable_list.h math_const.h)

target_include_directories(RayTracing PUBLIC ${PROJECT_BINARY_DIR})