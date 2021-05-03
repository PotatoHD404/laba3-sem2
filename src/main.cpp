#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
#endif

using namespace std;

#ifdef __EMSCRIPTEN__
EM_JS(string, do_fetch, (), {
return Asyncify.handleAsync(async () => {
out("waiting for a fetch");
        let promise = new Promise(function(resolve, reject){
            promiseResolve = resolve;
            promiseReject = reject;
        });
        out("got the fetch response");
        return await promise;
});
});
#else

string do_fetch() {
    string res;
    getline(cin, res);
    return res;
}

#endif


int say_hello(int a, int b) {
//    for (int i = 0; i < 1000000; ++i) {
//        int *c = new int[1024]();
//        if (i % 10000 == 0)
//            cout << 4.0 * i * 1024 / 1024 / 1024 << endl;
////        delete[] c;
//    }
//    int *c = new int[1024 * 1024 * 256]();
//    delete[] c;
    cout << "Hello from your wasm module " << a + b << endl;

    return a;
}

int main() {
    printf("hello, world!\n");
    return 0;
}


#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(Laba3) {
        emscripten::function("sayHello", &say_hello, emscripten::allow_raw_pointers());
}
#endif
