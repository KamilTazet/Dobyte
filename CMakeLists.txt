cmake_minimum_required(VERSION 3.20)

project(DepthOfMarket)

add_subdirectory(prog)

add_executable(main "")
target_sources(main
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

target_link_libraries(main PRIVATE prog)
add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

