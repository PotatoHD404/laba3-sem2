cmake_minimum_required(VERSION 3.19)
project(Laba3)

set(CMAKE_CXX_STANDARD 20)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../public/wasm)
    set(CMAKE_GCC_COMPILER "em++")
    set(CMAKE_C_COMPILER "emcc")
endif ()

add_executable(Laba3 main.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
#    set(CMAKE_EXECUTABLE_SUFFIX .mjs)
    set_target_properties(Laba3 PROPERTIES LINK_FLAGS "\
    -s WASM=1 \
    --bind \
    -s NODERAWFS=1 \
    -s ASSERTIONS=1 \
    -s EXPORT_ES6=1\
    -s ENVIRONMENT='node' \
    -s MODULARIZE=1\
    -s USE_ES6_IMPORT_META=0 \
    -s EXPORTED_RUNTIME_METHODS=['say_hello']")
endif ()