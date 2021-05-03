// noinspection JSFileReferences,NpmUsedModulesInstalled,JSUnresolvedFunction

import {useEffect} from 'react'
import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'

import Laba3WASM from './../public/wasm/Laba3.wasm'

// import Laba3WASM from './../public/wasm/Laba3.wasm';
let instance;

function click() {
    if (instance?.promiseResolve !== undefined) {
        console.log("workin)");
        instance.promiseResolve("32");
    }
    else {
        console.log("Not workin(");
    }
}

import Module from './../public/wasm/Laba3.js';

const Page = () => {
    useEffect(async () => {
        instance = await Module({
            locateFile: () => {
                return Laba3WASM
            },
        });

        console.log(instance.start());
    })

    return (
        <button onClick={click}>sometext</button>
    );
}

export default withRouter(Page)
