#include <cstdio>
#include <emscripten/bind.h>

using namespace emscripten;

int main() {
    printf("hello, world!\n");
    return 0;
}

int say_hello() {
    printf("Hello from your wasm module\n");
    return 0;
}

EMSCRIPTEN_BINDINGS(Laba3) {
        function("sayHello", &say_hello);
}

