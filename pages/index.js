import {withRouter} from 'next/router'
import dynamic from 'next/dynamic'
import Link from 'next/link'
import Wasm from "react-wasm";

const Main = () => (
    <Wasm url="/Laba3.wasm">
        {({ loading, error, data }) => {
            if (loading) return "Loading...";
            if (error) return "An error has occurred";

            const { module, instance } = data;
            return <div>1 + 2 = {instance.exports.add(1, 2)}</div>;
        }}
    </Wasm>
);

const Page = ({router: {query}}) => {
    const number = parseInt(query.number || 30)
    return (
        <div>
            <Main />
            <Link href={`/?number=${number + 1}`}>
                <a>+</a>
            </Link>
        </div>
    )
}

export default withRouter(Page)
