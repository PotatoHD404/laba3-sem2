//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
//#pragma GCC optimize("unroll-loops")

#include <iostream>
#include "Complex.hpp"
#include "NAryTree.hpp"
#include "Person.hpp"
#include "BTree.hpp"
//#include "Set.h"
#include <regex>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>

EM_JS(const char *, do_fetch, (), {
return Asyncify.handleAsync(async () => {
        let promise = new Promise(function(resolve, reject){
            Module.promiseResolve = resolve;
            Module.promiseReject = reject;
        });
        let res = await promise;
        let lengthBytes = lengthBytesUTF8(res)+1;
        let stringOnWasmHeap = _malloc(lengthBytes);
        stringToUTF8(res, stringOnWasmHeap, lengthBytes);
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


//int start() {
////    for (int i = 0; i < 10; ++i) {
////        string c = readline();
////        cout << "Hello from your wasm module " << i << " " << c << endl;
////    }
//    BTree<int> bTree(3);
//    for (int i = 0; i < 1500000; ++i) {
//        bTree.Insert(i);
////        cout << bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')") << endl;
//    }
//    cout << bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')") << endl;
////    cerr << "time taken : " << (float) clock() / CLOCKS_PER_SEC * 1000 << " milisecs" << endl;
//    return 0;
//}

int main() {
//    NAryTree<int> tree = NAryTree<int>("{1 7}({2})[{3}({4})[{5}]]", "{K}(1)[2]");
//    string order = tree.Order("{K}(1)[2]");
//    cout << order << endl;
//    NAryTree<int> res(order, "{K}(1)[2]");
//    Set<int> set = Set<int>();
//    int iterations = 1000;
//#ifdef __EMSCRIPTEN__
//    readline();
//    stringstream ss(readline());
//    ss >> iterations;
//#endif
//    std::random_device rd;
//    std::mt19937 mt(rd());
//    uniform_int_distribution<int> intDistro(0, iterations * 10);
    BTree<int> bTree(3);
    for (int i = 0; i < 10; ++i) {
        bTree.Insert(i);
    }
    cout << bTree.Order(R"((1)[2]{K}<3>d4b/5\"6')") << bTree.Count() << endl;
//    for (int i = 0; i < iterations; ++i) {
//        int tmp = intDistro(mt);
//        auto start = high_resolution_clock::now();
//        bTree.Insert(tmp);
//        auto stop = high_resolution_clock::now();
//        if (i % 10000 == 0) {
//            cout << "time taken : " << (float) duration_cast<nanoseconds>(stop - start).count() / 1000
//                 << " microseconds";
//            start = high_resolution_clock::now();
//            bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')");
//            stop = high_resolution_clock::now();
//            cout << " order time taken : " << (float) duration_cast<nanoseconds>(stop - start).count() / 1000000
//                 << " milliseconds"
//                 << " iteration #" << i << endl;
//        }
//    }
//    bTree.Remove(8);
//    bTree.Remove(17);
//    cout << bTree.Order(R"({K}(1)[2]<3>d4b/5\"6')") << endl;
//    cout << "time taken : " << (float) clock() / CLOCKS_PER_SEC << " secs" << endl;
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
        emscripten::function("start", &main, emscripten::allow_raw_pointers());
}
#endif