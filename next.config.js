module.exports = {
    webpack(config, {isServer}) {
        config.output.webassemblyModuleFilename = 'static/build/[modulehash].build'
        config.module.rules.push({
                test: /\.(wasm)$/,
                loader: 'file-loader',
                type: 'javascript/auto',
                options: {
                    outputPath: 'static',
                },
            }

            // Overcome Webpack referencing `window` in chunks

        )
        config.output.globalObject = `(typeof self !== 'undefined' ? self : this)`
        if (!isServer) {
            config.node = {
                fs: 'empty'
            }
        }
        return config
    },
}
// const withPWA = require('next-pwa')
// module.exports = withPWA({
//     webpack(config, {isServer}) {
//         config.output.webassemblyModuleFilename = 'static/build/[modulehash].build'
//         config.module.rules.push({
//                 test: /\.(wasm)$/,
//                 loader: 'file-loader',
//                 type: 'javascript/auto',
//                 options: {
//                     outputPath: 'static',
//                 },
//             }
//
//             // Overcome Webpack referencing `window` in chunks
//
//         )
//         config.output.globalObject = `(typeof self !== 'undefined' ? self : this)`
//         if (!isServer) {
//             config.node = {
//                 fs: 'empty'
//             }
//         }
//         return config
//     },
//     pwa: {
//         dest: "public"
//     }
// })
