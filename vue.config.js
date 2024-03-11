const {defineConfig} = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: false,
  pluginOptions: {
    electronBuilder: {
      nodeIntegration: true,
      builderOptions: {
        productName: 'DBManager',
        directories: {
          output: 'dist_electron'
        },
        asar: false,
        win: {
          icon: './public/logo.ico',
          artifactName: '${productName}-${platform}-${arch}-${version}.${ext}',
          target: [
            {
              target: 'nsis',
              arch: ['x64']
            },
            {
              target: 'portable',
              arch: ['x64']
            }
          ]
        },
        nsis: {
          artifactName: '${productName}-${platform}-${arch}-${version}-nsis.${ext}',
          oneClick: false,
          perMachine: false,
          allowElevation: true,
          allowToChangeInstallationDirectory: true,
          deleteAppDataOnUninstall: true,
          createDesktopShortcut: false,
          createStartMenuShortcut: true
        }
      }
    }
  }
})
