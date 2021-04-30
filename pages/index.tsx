import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Link from 'next/link'

const Main = dynamic({
    loader: async () => {
        // Import the wasm module
        // @ts-ignore
        const Laba = await import('../main.wasm')
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
