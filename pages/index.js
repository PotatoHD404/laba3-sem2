// noinspection JSFileReferences,NpmUsedModulesInstalled,JSUnresolvedFunction
// noinspection JSUnresolvedVariable

import Head from "next/head";
import {useEffect} from 'react'
import {withRouter} from 'next/router'

const Page = () => {
    let worker;
    let ok;
    useEffect(async () => {
        // let instance = await Laba3({
        //     'print': (data) => {
        //         postMessage(data);
        //     },
        //     locateFile: () => {
        //         return Laba3WASM
        //     },
        // });

        worker = new Worker('/workers/main.worker.js', {type: "module"});
        worker.addEventListener('message', (e) => {
            if (e && e.data) {
                print(e.data);
            }
        });
        ok = false;
        worker.postMessage('init');
        // }, [worker]);
        // useEffect(() => {
        //
        //     // this.worker.postMessage('from Host');
        //     // worker.addEventListener('message', function (e) {
        //     //
        //     // });
        // });
    });
    // <option value="int">int</option>
    // <option value="double">double</option>
    // <option value="float">float</option>
    // <option value="complex">complex</option>
    // <option value="functions">functions</option>
    // <option value="people">people</option>
    // <option value="strings">strings</option>
    function Command(input) {
        if (ok) {
            ok = false;
            let set;
            switch (input) {
                case 'type':
                    let mess;
                    switch (document.getElementById("typeSelect").value) {
                        case 'int':
                            mess = '1';
                            break;
                        case 'double':
                            mess = '2';
                            break;
                        case 'float':
                            mess = '3';
                            break;
                        case 'complex':
                            mess = '4';
                            break;
                        // case 'functions':
                        //     mess = '5';
                        //     break;
                        case 'people':
                            mess = '6';
                            break;
                        case 'strings':
                            mess = '7';
                            break;
                    }
                    document.getElementById("type").classList.add("d-none");
                    document.getElementById("menu").classList.remove("d-none");
                    worker.postMessage(mess + "\n" + '3' + "\n" + '1' + "\n" + '3' + "\n" + '2');
                    break;
                case 'input':
                    switch (document.getElementById("InputSelect").value) {
                        case 'a':
                            set = '1';
                            break;
                        case 'b':
                            set = '2';
                            break;
                    }
                    worker.postMessage('1' + "\n" + set + "\n" + document.getElementById("setInput").value + "\n" + '3' + "\n" + set);
                    break;
                case 'remove':
                    switch (document.getElementById("RemoveSelect").value) {
                        case 'a':
                            set = '1';
                            break;
                        case 'b':
                            set = '2';
                            break;
                    }
                    worker.postMessage('2' + "\n" + set + "\n" + document.getElementById("setRemove").value + "\n" + '3' + "\n" + set);
                    break;
                case 'asSequence':
                    switch (document.getElementById("ArrayPrintSelect").value) {
                        case 'a':
                            set = '1';
                            break;
                        case 'b':
                            set = '2';
                            break;
                    }
                    worker.postMessage('4' + "\n" + set + "\n" + '3' + "\n" + set);
                    break;
                case 'asTree':
                    switch (document.getElementById("treePrintSelect").value) {
                        case 'a':
                            set = '1';
                            break;
                        case 'b':
                            set = '2';
                            break;
                    }
                    worker.postMessage('5' + "\n" + set + "\n" + '3' + "\n" + set);
                    break;
                case 'check':
                    switch (document.getElementById("RemoveSelect").value) {
                        case 'a':
                            set = '1';
                            break;
                        case 'b':
                            set = '2';
                            break;
                    }
                    worker.postMessage('6' + "\n" + set + "\n" + document.getElementById("checkValue").value + "\n" + '3' + "\n" + set);
                    break;
                case 'sum':
                    worker.postMessage('7');
                    break;
                case 'multiply':
                    worker.postMessage('8');
                    break;
                case 'subtract':
                    worker.postMessage('9');
                    break;
            }
        }
    }

    function print(data) {
        ok = true;
        // console.log(data);
        if (data.includes("Result Set A: {"))
            document.getElementById("setA").value = data.split("Result Set A: ")[1];
        else if (data.includes("Result Set B: {"))
            document.getElementById("setB").value = data.split("Result Set B: ")[1];
        else if (data.includes("Result: "))
            document.getElementById("result").value = data.split("Result: ")[1];
        else if(data.includes("Set does not contain the value"))
            document.getElementById("result").value = "Set does not contain the value";
        else if(data.includes("Set contains the value"))
            document.getElementById("result").value = "Set contains the value";

        document.getElementById("consoleOutput").innerHTML += data + '\r\n';
        let textarea = document.getElementById("consoleOutput");
        let temp = textarea.scrollTop;
        let interval = setInterval(() => {
            let end = textarea.scrollHeight;
            if (temp < end) {
                textarea.scrollTop += 50;
                temp += 50;
            } else {
                clearInterval(interval);
            }
        }, 5);

    }

    // componentDidMount() {
    //
    // }
    // componentWillUnmount() {
    //     this.worker.terminate();
    // }

    return (<>
            <Head>
                <meta name="viewport" content="width=device-width, initial-scale=1"/>
                <title>PotatoHD</title>
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

                            <select className="form-select" aria-label="" id="typeSelect">
                                <option value="int">int</option>
                                <option value="double">double</option>
                                <option value="float">float</option>
                                <option value="complex">complex</option>
                                {/*<option value="functions">functions</option>*/}
                                <option value="people">people</option>
                                <option value="strings">strings</option>
                            </select>

                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("type")}>Set type
                                </button>
                            </div>
                        </div>
                    </div>
                    <div className="col-lg-4 col-md-6 d-none" id="menu">
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">

                                <select className="form-select" aria-label="" id="InputSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>

                            </div>
                            <input type="text" className="form-control" id="setInput"
                                   placeholder="Add value to set"
                                   aria-label="input"/>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("input")}>Input
                                </button>
                            </div>
                            <div className="invalid-feedback">
                                Invalid input
                            </div>
                            <div className="valid-feedback">
                                Your input was sent
                            </div>
                        </div>
                        {/*3. Print set*/}
                        {/*4. Convert set to ArraySequence and print*/}
                        {/*5. Check if set contains value*/}
                        {/*6. Calculate union of sets*/}
                        {/*7. Calculate intersection of sets*/}
                        {/*8. Calculate difference of sets*/}
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">

                                <select className="form-select" aria-label="" id="RemoveSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>

                            </div>
                            <input type="text" className="form-control" id="setRemove"
                                   placeholder="Remove value from set"
                                   aria-label="input"/>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("remove")}>Remove
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
                                <select className="form-select" aria-label="" id="checkValueSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>
                            </div>
                            <input type="text" className="form-control" placeholder="Input value to check"
                                   aria-label="input"
                                   id="checkValue"/>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("check")}>Check
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

                                <select className="form-select" aria-label="" id="ArrayPrintSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>

                            </div>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("asSequence")}>Print as ArraySequence
                                </button>
                            </div>
                            <div className="invalid-feedback">
                                Invalid input
                            </div>
                            <div className="valid-feedback">
                                Your input was sent
                            </div>
                        </div>

                        <div className="input-group mb-3 ">
                            <div className="input-group-prepend">
                                <select className="form-select" aria-label="" id="treePrintSelect">
                                    <option value="a">A</option>
                                    <option value="b">B</option>
                                </select>
                            </div>
                            <div className="input-group-append">
                                <button className="btn btn-outline-secondary" type="button"
                                        onClick={() => Command("asTree")}>Print as tree
                                </button>
                            </div>
                            <div className="invalid-feedback">
                                Invalid input
                            </div>
                            <div className="valid-feedback">
                                Your input was sent
                            </div>
                        </div>


                        <div className="input-group mb-3 justify-content-center">
                            <button className="btn btn-outline-secondary" type="button"
                                    onClick={() => Command("sum")}>Union of A and B
                            </button>
                            <button className="btn btn-outline-secondary" type="button"
                                    onClick={() => Command("multiply")}>Intersection of A and B
                            </button>
                            <button className="btn btn-outline-secondary" type="button"
                                    onClick={() => Command("subtract")}>Difference of A and B
                            </button>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <span className="input-group-text">Set A</span>
                            </div>
                            <input type="text" className="form-control" placeholder="" id="setA" aria-label="Set A"
                                   readOnly/>
                        </div>
                        <div className="input-group mb-3">
                            <div className="input-group-prepend">
                                <span className="input-group-text">Set B</span>
                            </div>
                            <input type="text" className="form-control" placeholder="" id="setB" aria-label="Set B"
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
