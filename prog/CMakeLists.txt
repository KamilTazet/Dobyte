cmake_minimum_required(VERSION 3.10)

project(prog)

add_library(prog "")

target_sources(prog 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/Order.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/DOM_1.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/DOM_2.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/DOM_3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/DOM_4.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/DOM_5.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Test.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/Order.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM_1.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM_2.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM_3.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM_4.h
        ${CMAKE_CURRENT_LIST_DIR}/include/DOM_5.h
        ${CMAKE_CURRENT_LIST_DIR}/include/Test.h
)

target_include_directories(prog PUBLIC include)
