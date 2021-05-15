#!/bin/bash
EM_PATH=$HOME/emsdk/upstream/emscripten
mkdir -p ./src/cmake-build-webassembly
rm -rf ./src/cmake-build-webassembly/*
cd ./src/cmake-build-webassembly && "${EM_PATH}"/emcmake cmake ./../ && "${EM_PATH}"/emmake make
rm -rf ./../bindings
find ./ -name "*.ts" -delete