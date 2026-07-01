cmake_minimum_required(VERSION 3.10)
project(SDL3_stduy)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)

find_package(SDL3 REQUIRED)

if(NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
else()
    message(STATUS "Using local SDL3")
endif()

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

target_link_libraries(main PRIVATE SDL3::SDL3)