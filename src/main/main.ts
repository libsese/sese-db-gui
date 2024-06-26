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

ipcMain.on('open_url', async (event, url: string) => {
  await shell.openExternal(url)
})

// 模块重定位
let module_path: string
if (process.env.NODE_ENV === 'development') {
  // D:/workspaces/sese-db-gui/build/Release/DBExport.node
  console.log(module_path = join(process.cwd(), '/'));
} else {
  // D:/DBManager/resources/build/Release/DBExport.node
  console.log(module_path = join(process.cwd(), '/resources'));
}

const db = require('bindings')({
  bindings: 'DBExport',
  module_root: module_path
})
import {Connect} from 'typings/db';

let conn: Connect

ipcMain.on('open_db', (event, host: string, port: Number, db_name: string, user: string, pwd: string) => {
  const conn_string = 'host=' + host + ';port=' + port + ';db=' + db_name + ';user=' + user + ';pwd=' + pwd + ';';

  conn = db.CreateMySQLConnect(conn_string)
})

ipcMain.handle('get_tables', (event, db_name: string) => {
  const sql = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='" + db_name + "';";
  const res = conn.executeQuery(sql);
  const tables: string[] = [];
  while (res.next()) {
    tables.push(res.getText(0))
  }
  return tables;
})

ipcMain.handle('get_table_headers', (event, db_name: string, tb_name: string) => {
  const sql = "SELECT column_name FROM information_schema.columns WHERE table_schema = '" + db_name + "' AND table_name = '" + tb_name + "';";
  const res = conn.executeQuery(sql);
  const headers: string[] = [];
  while (res.next()) {
    headers.push(res.getText((0)))
  }
  return headers;
})

ipcMain.handle('get_table_contents', (event, tb_header: string[], tb_name: string) => {
  let sql = "SELECT ";
  let first = true;
  for (let i = 0; i < tb_header.length; i++) {
    const header = tb_header[i];
    if (first) {
      first = false;
      sql += header;
    } else {
      sql += "," + header
    }
  }
  sql += " FROM " + tb_name + " LIMIT 255;"
  console.log(sql);
  const res = conn.executeQuery(sql);
  const length = res.getColumns();
  const contents: string[] = [];
  while (res.next()) {
    for (let i = 0; i < length.valueOf(); i++) {
      if (res.isNull(i)) {
        contents.push('[NULL]')
      } else {
        contents.push(res.getText(i))
      }
    }
  }
  return contents;
})