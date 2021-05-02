module.exports = {
  module: {
    rules: [
      {
        test: /\.(wasm)$/,
        loader: 'file-loader',
        type: 'javascript/auto',
      },
    ],
  },
  webpack(config, { isServer }) {
    config.output.webassemblyModuleFilename = 'static/build/[modulehash].build'
    if (!isServer) {
      config.node = {
        fs: 'empty'
      }
    }
    return config
  },
}
