### Preamble ###
cmake_minimum_required(VERSION 3.15)
project(Test VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Dependencies ###
include_directories(src)
include_directories(dependencies)
add_subdirectory(dependencies)

### Main Targets ###
add_subdirectory(src)
add_subdirectory(tests)