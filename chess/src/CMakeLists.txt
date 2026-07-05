file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "./*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_library(core ${SOURCES})

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../third-party/raylib/lib/libraylib.a")

target_include_directories(core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/../third-party/raylib/include")
target_compile_options(core PRIVATE ${SANITIZE_FLAGS})
target_link_options(core PRIVATE ${SANITIZE_FLAGS})
target_link_libraries(core PRIVATE raylib X11)

add_executable(
  app.elf
    ./main.cpp
)

target_include_directories(app.elf PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/../third-party/raylib/include")
target_compile_options(app.elf PRIVATE ${SANITIZE_FLAGS})
target_link_options(app.elf PRIVATE ${SANITIZE_FLAGS})
target_link_libraries(app.elf PRIVATE core)
