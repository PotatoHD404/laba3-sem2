import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Link from 'next/link'
import { WASI } from 'wasi';

const Main = dynamic({
    loader: async () => {
        // Import the wasm module
        let memory = new WebAssembly.Memory({initial:10, maximum:100});
        const Laba = await import('../wasm/main.wasm')
        WebAssembly.instantiateStreaming(Laba, { js: { mem: memory } })
            .then(obj => {
                var i32 = new Uint32Array(memory.buffer);
                for (var i = 0; i < 10; i++) {
                    i32[i] = i;
                }
                var sum = obj.instance.exports.accumulate(0, 10);
                console.log(sum);
            });
        // Return a React component that calls the add_one method on the wasm module
        return (props) => <div>{Laba.main()}</div>
    },
})

const Page = ({router: {query}}) => {
    const number = parseInt(query.number || 30)
    return (
        <div>
            <Main number={number}/>
            <Link href={`/?number=${number + 1}`}>
                <a>+</a>
            </Link>
        </div>
    )
}

export default withRouter(Page)
