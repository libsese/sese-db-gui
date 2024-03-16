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
        },
        files: [
          "**/*",
          "!**/node_modules/*/{CHANGELOG.md,README.md,README,readme.md,readme}",
          "!**/node_modules/*/{test,__tests__,tests,powered-test,example,examples}",
          "!**/node_modules/*.d.ts",
          "!**/node_modules/.bin",
          "!**/*.{iml,o,hprof,orig,pyc,pyo,rbc,swp,csproj,sln,xproj}",
          "!.editorconfig",
          "!**/._*",
          "!**/{.DS_Store,.git,.hg,.svn,CVS,RCS,SCCS,.gitignore,.gitattributes}",
          "!**/{__pycache__,thumbs.db,.flowconfig,.idea,.vs,.nyc_output}",
          "!**/{appveyor.yml,.travis.yml,circle.yml}",
          "!**/{npm-debug.log,yarn.lock,.yarn-integrity,.yarn-metadata.json}"
        ]
      }
    }
  }
})
