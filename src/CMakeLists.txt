cmake_minimum_required(VERSION 3.19)
project(Laba3)

set(CMAKE_CXX_STANDARD 20)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../public)
    set(CMAKE_C_COMPILER "em++")
endif ()

add_executable(Laba3 main.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(Laba3 PROPERTIES LINK_FLAGS "-o dist/engine.js -s DISABLE_EXCEPTION_CATCHING=0 -s SAFE_HEAP=1 --bind -s WASM=1 -O2 -std=c++20 -s FULL_ES3=1")
endif ()