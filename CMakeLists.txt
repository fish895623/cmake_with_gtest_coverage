cmake_minimum_required(VERSION 3.20)

project(ccoverage)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/sources/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/includes)
