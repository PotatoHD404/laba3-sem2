import Laba3 from "/scripts/Laba3.js";

// import Laba3WASM from './../../scripts/Laba3.wasm';
// import { messageTypes } from './main.js' // this is the cause

function cin(input) {
    if (self.instance?.promiseResolve !== undefined) {
        let tmp = self.instance.promiseResolve;
        self.instance.promiseResolve = undefined;
        tmp(input);
    } else {
        console.log("Not responding to promise");
    }
}


self.onmessage = async (e) => {
    if (e.data === 'init') {
        self.instance = await Laba3({
            'print': (data) => {
                postMessage(data);
            },
        });
        self.instance.start();
    } else {
        cin(e.data);
    }
}