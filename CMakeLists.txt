cmake_minimum_required(VERSION 3.12)
project(win32test)

add_executable(win32test WIN32 src/main.cpp)
set_property(TARGET win32test PROPERTY CXX_STANDARD 20)
target_include_directories(win32test PRIVATE include)
