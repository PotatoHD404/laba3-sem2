// noinspection JSFileReferences,NpmUsedModulesInstalled,JSUnresolvedFunction

import {useEffect} from 'react'
import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Module from './../public/wasm/Laba3.worker.js';
import Laba3WASM from './../public/wasm/Laba3.wasm'
// import Laba3WASM from './../public/wasm/Laba3.wasm';
let promiseResolve, promiseReject;
const Page = () => {
    useEffect(async () => {
        let instance = await Module({
            locateFile: () => {
                return Laba3WASM
            },
        });
        promiseResolve();
        console.log(instance.sayHello(3, 5));
    })

    return (
        <div/>
    );
}

export default withRouter(Page)
