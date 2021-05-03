module.exports = {
    webpack (config, { isServer }) {
        config.output.webassemblyModuleFilename = 'static/build/[modulehash].build'
        config.module.rules.push({
            test: /\.(wasm)$/,
            loader: 'file-loader',
            type: 'javascript/auto',
            options: {
                outputPath: 'static',
            },
        })
        if (!isServer) {
            config.node = {
                fs: 'empty'
            }
        }
        return config
    },
}
