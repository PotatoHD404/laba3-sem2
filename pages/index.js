// noinspection JSFileReferences,NpmUsedModulesInstalled,JSUnresolvedFunction
import Head from "next/head";
import {useEffect} from 'react'
import {withRouter} from 'next/router'

process.hrtime = require('browser-process-hrtime')

import Module from './../scripts/Laba3.js';
import Laba3WASM from './../scripts/Laba3.wasm'


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
                console.log(data);
            },
            locateFile: () => {
                return Laba3WASM
            },
        });

        console.log(instance.start());
    })

    return (<>
            <Head>
                <meta name="viewport" content="width=device-width, initial-scale=1"/>
                <title>Main</title>
            </Head>
            <div className={"container-fluid"}>
                <div className={"row mt-5 justify-content-center "}>
                    <div className={"col-5 d-flex justify-content-center"}>
                        <button className={"btn btn-outline-secondary align-self-start mt-3"} onClick={click}>Start</button>
                    </div>
                    <div className={"col-5"}>
                        <div className={"row"}>
                        <textarea className="form-control mb-3 mt-2" id="consoleOutput" rows="5"
                                  readOnly/></div>
                    </div>
                </div>
            </div>


        </>
    );
}

export default withRouter(Page)
