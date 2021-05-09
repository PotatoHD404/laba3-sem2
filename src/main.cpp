#include <iostream>
#include "Complex.h"
#include "NAryTree.h"
#include "Person.h"
#include "BTree.h"
#include <regex>

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
//    NAryTree<int> tree = NAryTree<int>("{1 7}({2})[{3}({4})[{5}]]", "{K}(1)[2]");
//    string order = tree.Order("{K}(1)[2]");
//    cout << order << endl;
//    NAryTree<int> res(order, "{K}(1)[2]");
    BTree<int> bTree;
    bTree.Insert(10);
    bTree.Insert(20);
    bTree.Insert(30);
    bTree.Insert(40);
    bTree.Insert(50);
    bTree.Insert(60);
    bTree.Insert(70);
    bTree.Insert(80);
    bTree.Insert(90);
    cout << bTree.Order("{K}(1)[2]<3>d4b\\5/") << endl;
    return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &start, emscripten::allow_raw_pointers());
}
#endif