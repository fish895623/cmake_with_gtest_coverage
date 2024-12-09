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
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/sources/main.cpp")

enable_testing()
add_executable(
  ${PROJECT_NAME}_test
  ${TESTS}
  ${SOURCES}
)
target_include_directories(
  ${PROJECT_NAME}_test PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(
  ${PROJECT_NAME}_test
  GTest::gtest_main
)
target_compile_options(${PROJECT_NAME}_test PRIVATE
-coverage
)
target_link_options(${PROJECT_NAME}_test PRIVATE
-coverage
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)

add_custom_target(
  run_tests
  DEPENDS ${PROJECT_NAME}_test
  COMMAND ctest --output-on-failure)
add_custom_target(
  coverage_report
  DEPENDS run_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND gcovr -r . --exclude build --exclude tests --html --html-details -o coverage_report.html
)
