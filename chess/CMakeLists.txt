cmake_minimum_required(VERSION 3.20)
project(app.elf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(SANITIZE)
  set(SANITIZE_FLAGS 
    -fsanitize=address 
    -fsanitize=undefined 
    -fsanitize=leak 
    -fno-omit-frame-pointer 
    -g
  )
endif()

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

add_subdirectory(src)