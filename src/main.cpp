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
    BTree<int> bTree(3);
    for (int i = 0; i < 28; ++i) {
        bTree.Insert(i);
        cout << bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')") << endl;
    }
    bTree.Remove(8);
    bTree.Remove(17);
    cout << bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')") << endl;
//    for (int i = 0; i < 19; ++i) {
//        if(i == 9)
//            int a = 0;
//        cout << bTree.Search(i) << endl;
//    }
//        bTree.Insert(0);
//        cout << bTree.Order("{K}(1)[2]<3>d4b\\5/") << endl;
//    bTree.Remove(8);
//    cout << bTree.Order("{K}(1)[2]<3>d4b\\5/") << endl;
    return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("start", &start, emscripten::allow_raw_pointers());
}
#endif