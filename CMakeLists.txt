cmake_minimum_required(VERSION 3.10)
project(match3 C)

set(CMAKE_C_STANDARD 99)

find_package(raylib REQUIRED)

add_executable(match3 src/main.c)

target_link_libraries(match3 raylib)

target_include_directories(match3 PRIVATE ${raylib_INCLUDE_DIRS})

add_custom_command(TARGET match3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:match3>/assets
)
