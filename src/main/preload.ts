import {contextBridge, ipcRenderer} from 'electron';

contextBridge.exposeInMainWorld('electronAPI', {
  open_url: (url: string) => ipcRenderer.send('open_url', url),
  open_db: (host: String, port: Number, db: String, user: String, pwd: String) =>
    ipcRenderer.send('open_db', host, port, db, user, pwd)
})