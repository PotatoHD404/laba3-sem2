#!/bin/bash
EM_PATH=/home/potatohd/emsdk/upstream/emscripten
mkdir -p ./src/cmake-build-webassembly ./public/wasm
rm -rf ./src/cmake-build-webassembly/* ./public/wasm/*
cd ./src/cmake-build-webassembly && ${EM_PATH}/emcmake cmake ./../ && ${EM_PATH}/emmake make
rm -rf ./../bindings