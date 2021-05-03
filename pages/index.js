// noinspection JSFileReferences,NpmUsedModulesInstalled
import {useEffect} from 'react'
import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Module from './../public/wasm/Laba3.js';
import Laba3WASM from './../public/wasm/Laba3.wasm'
// import Laba3WASM from './../public/wasm/Laba3.wasm';

const Page = () => {
    useEffect(async () => {
        let instance = await Module({
            locateFile: () => {
                return Laba3WASM
            },
        })
        console.log(instance.sayHello());
    })

    return (
        <div/>
    );
}

export default withRouter(Page)
