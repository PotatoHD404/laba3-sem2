// noinspection JSFileReferences,NpmUsedModulesInstalled

import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Laba3 from './../public/wasm/Laba3.js';
// import './../public/wasm/Laba3.wasm' as Laba3WASM;
// const Sample = Laba3({
//     locateFile: () => {
//         return Laba3WASM;
//     },
// });

const Page = () => {
    const instance = Laba3({
        onRuntimeInitialized() {
            instance.sayHello();
        }
    });

    return (
        <div/>
    );
}

export default withRouter(Page)
