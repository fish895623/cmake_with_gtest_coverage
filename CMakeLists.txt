cmake_minimum_required(VERSION 3.20)

project(ccoverage)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/sources/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/includes)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

# Test case
file(GLOB TESTS "${CMAKE_SOURCE_DIR}/tests/*.cpp")

enable_testing()
add_executable(
  ${PROJECT_NAME}_test
  ${TESTS}
  ${SOURCES}
)
target_include_directories(${PROJECT_NAME}_test PRIVATE
  ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(
  ${PROJECT_NAME}_test
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
