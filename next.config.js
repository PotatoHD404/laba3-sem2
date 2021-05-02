module.exports = {
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
