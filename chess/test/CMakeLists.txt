cmake_minimum_required(VERSION 3.20)
project(test.elf LANGUAGES CXX)

find_package(GTest REQUIRED)

file(GLOB_RECURSE
  TEST_SOURCES
  CONFIGURE_DEPENDS "unit/*.cpp"
)

add_executable(
  ${PROJECT_NAME}
    ./main.cpp
    ${TEST_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GTest::Main)
target_include_directories(${PROJECT_NAME} PRIVATE ../include)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
