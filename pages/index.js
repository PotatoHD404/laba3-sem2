// noinspection JSFileReferences,NpmUsedModulesInstalled,JSUnresolvedFunction

import {useEffect} from 'react'
import {withRouter} from 'next/router'

import Module from './../public/wasm/Laba3.js';
import Laba3WASM from './../public/wasm/Laba3.wasm'


let instance;

function click() {
    if (instance?.promiseResolve !== undefined) {
        console.log("workin)");
        instance.promiseResolve("32");
    } else {
        console.log("Not workin(");
    }
}


const Page = () => {
    useEffect(async () => {
        instance = await Module({
            'print': (data) => {
                console.log("Working!!!");
            },
            locateFile: () => {
                return Laba3WASM
            },
        });

        console.log(instance.start());
    })

    return (<div>
            <graph indexType="custom" height="400" width="400" nodes={[{label: 0, center: {x: 203.3, y: 68.3}}, {
                label: "1",
                center: {x: 60, y: 214.6}
            }, {label: "2", center: {x: 401.5, y: 123.6}}, {label: 3, center: {x: 146.1, y: 401.5}}, {
                label: 4,
                center: {x: 326.5, y: 314.7}
            }]} edges={[{source: 0, target: 1}, {source: 0, target: 2}, {source: 4, target: 2}, {
                source: 3,
                target: 1
            }]}/>
            <button onClick={click}>sometext</button>
        </div>
    );
}

export default withRouter(Page)
