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
            <div className="container-fluid">
                <div className="row mt-5 justify-content-center">
                    <div className="col-lg-5 col-md-8 justify-content-center text-center">
                        <label htmlFor="consoleOutput">Console output</label>
                        <textarea className="form-control mb-3 mt-2" id="consoleOutput" rows="5" readOnly/>
                    </div>
                </div>
                <div className="row justify-content-center">
                    <div className="col-lg-4 col-md-6" id="type">
                        <div className="input-group mb-3">

                            <select className="form-select" aria-label="Default select example" id="typeSelect">
                                <option value="int">int</option>
                                <option value="float">float</option>
                                <option value="complex">complex</option>
                            </select>

                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={Command("type")}>Set type
                                </button>
                            </div>
                        </div>
                    </div>
                    <div className="col-lg-4 col-md-6 d-none" id="menu">
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">

                                <select className="form-select" aria-label="Default select example" id="setSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>

                            </div>
                            <input type="text" className="form-control" id="setInput"
                                   placeholder="Set polynomial (1 2 3 4)"
                                   aria-label="input"/>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={Command("input")}>Set
                                </button>
                            </div>
                            <div className="invalid-feedback">
                                Invalid input
                            </div>
                            <div className="valid-feedback">
                                Your input was sent
                            </div>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">

                                <select className="form-select" aria-label="Default select example"
                                        id="scalarMultiplySelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>

                            </div>
                            <input type="text" className="form-control" placeholder="Multiply poly on scalar"
                                   aria-label="input"
                                   id="scalarMultiplyInput"/>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={Command("scalarMultiply")}>
                                    Multiply
                                </button>
                            </div>
                            <div className="invalid-feedback">
                                Invalid input
                            </div>
                            <div className="valid-feedback">
                                Your input was sent
                            </div>
                        </div>

                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <select className="form-select" aria-label="Default select example" id="calcPolySelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>
                            </div>
                            <input type="text" className="form-control" placeholder="Calculate poly in x"
                                   aria-label="input"
                                   id="calcPolyInput">
                                <div className="input-group-append">
                                    <button className="btn btn-outline-secondary" type="button"
                                            onClick={Command("calc")}>Calculate
                                    </button>
                                </div>
                                <div className="invalid-feedback">
                                    Invalid input
                                </div>
                                <div className="valid-feedback">
                                    Your input was sent
                                </div>
                            </input>
                        </div>

                        <div className="input-group mb-3 justify-content-center">
                            <button className="btn btn-outline-secondary" type="button" onClick={Command("sum")}>Sum A
                                and
                                B
                            </button>
                            <button className="btn btn-outline-secondary" type="button"
                                    onClick={Command("multiply")}>Multiply A and B
                            </button>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <span className="input-group-text">Poly A</span>
                            </div>
                            <input type="text" className="form-control" placeholder="" id="polyA" aria-label="Poly A"
                                   readOnly/>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <span className="input-group-text">Poly B</span>
                            </div>
                            <input type="text" className="form-control" placeholder="" id="polyB" aria-label="Poly B"
                                   readOnly/>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <span className="input-group-text">Result</span>
                            </div>
                            <input type="text" className="form-control" placeholder="" id="result" aria-label="Result"
                                   readOnly/>
                        </div>
                    </div>
                </div>

            </div>


        </>
    );
}

export default withRouter(Page)
