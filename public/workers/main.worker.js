import Laba3 from "/scripts/Laba3.js";

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