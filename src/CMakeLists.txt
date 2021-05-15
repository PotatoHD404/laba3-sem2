cmake_minimum_required(VERSION 3.19)
project(Laba3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../scripts)
    set(CMAKE_GCC_COMPILER "em++")
    set(CMAKE_C_COMPILER "emcc")
endif ()

add_executable(Laba3 main.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
#    set(CMAKE_EXECUTABLE_SUFFIX .mjs)
    set_target_properties(Laba3 PROPERTIES LINK_FLAGS "\
    -s WASM=1 \
    --bind \
    --no-entry \
    -s ALLOW_MEMORY_GROWTH \
    -s MALLOC=emmalloc \
    -s ASSERTIONS \
    -s EXPORT_ES6 \
    -s ENVIRONMENT='node' \
    -s MODULARIZE \
    -s NO_USE_ES6_IMPORT_META \
    -s ASYNCIFY \
    -s 'ASYNCIFY_IMPORTS=[\"do_fetch\"]'")
endif ()