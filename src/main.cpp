#include <iostream>
#include "Complex.h"
#include "NAryTree.h"
#include "Person.h"

using namespace std;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>

EM_JS(const char *, do_fetch, (), {
return Asyncify.handleAsync(async () => {
out("waiting for a fetch");
        let promise = new Promise(function(resolve, reject){
            Module.promiseResolve = resolve;
            Module.promiseReject = reject;
        });
        let res = await promise;
        let lengthBytes = lengthBytesUTF8(res)+1;
        let stringOnWasmHeap = _malloc(lengthBytes);
        stringToUTF8(res, stringOnWasmHeap, lengthBytes);

        out("got the fetch response");
        return stringOnWasmHeap;
});
});

string readline(){
    const char * input = do_fetch();
    string res = input;
    delete[] input;
    return res;
}
#else

string readline() {
    string res;
    getline(cin, res);
    return res;
}

#endif


int start() {
    for (int i = 0; i < 10; ++i) {
        string c = readline();
        cout << "Hello from your wasm module " << i << " " << c << endl;
    }
    return 0;
}

int main() {
    
    return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &start, emscripten::allow_raw_pointers());
}
#endif