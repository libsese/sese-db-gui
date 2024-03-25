import {app, BrowserWindow, ipcMain, session, shell} from 'electron';
import {join} from 'path';

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    minWidth: 800,
    minHeight: 600,
    title: '数据库管理器',
    titleBarStyle: 'hidden',
    titleBarOverlay: {
      color: '#383a42',
      symbolColor: 'white',
      height: 40
    },
    icon: join(__dirname, 'static/logo.png'),
    webPreferences: {
      preload: join(__dirname, 'preload.js'),
      nodeIntegration: false,
      contextIsolation: true,
      sandbox: false
    }
  });

  if (process.env.NODE_ENV === 'development') {
    const rendererPort = process.argv[2];
    mainWindow.loadURL(`http://localhost:${rendererPort}`);
    mainWindow.webContents.openDevTools({mode: 'detach'})
  } else {
    mainWindow.loadFile(join(app.getAppPath(), 'renderer', 'index.html'));
  }
}

app.whenReady().then(() => {
  createWindow();

  session.defaultSession.webRequest.onHeadersReceived((details, callback) => {
    callback({
      responseHeaders: {
        ...details.responseHeaders,
        'Content-Security-Policy': ['script-src \'self\'']
      }
    })
  })

  if (process.env.NODE_ENV === 'development') {
    console.log(join(process.cwd(), '/build/Release'));
  } else {
    console.log(join(process.cwd(), '/resource/lib'));
  }

  app.on('activate', function () {
    // On macOS it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
});

// Native API

ipcMain.on('open_url', (event, url: string) => {
  shell.openExternal(url).then(r => {
  })
})

const db = require('bindings')('DBExport')
import {Connect} from 'db';

let conn: Connect

ipcMain.on('open_db', (event, host: String, port: Number, db_name: String, user: String, pwd: String) => {
  const conn_string = 'host=' + host + ';port=' + port + ';db=' + db_name + ';user=' + user + ';pwd=' + pwd + ';';

  conn = db.CreateMySQLConnect(conn_string)
})

ipcMain.handle('get_tables', (event, db_name: String) => {
  const sql = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='"+ db_name + "';";
  const res = conn.executeQuery(sql);
  const tables: String[] = [];
  while(res.next()) {
    tables.push(res.getText(0))
  }
  return tables;
}) 