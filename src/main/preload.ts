import { contextBridge, ipcRenderer } from 'electron';

contextBridge.exposeInMainWorld('electronAPI', {
  open_url: (url: string) => ipcRenderer.send('open_url', url),
  open_db: (host: string, port: Number, db: string, user: string, pwd: string) =>
    ipcRenderer.send('open_db', host, port, db, user, pwd),
  get_tables: (db_name: string) => { return ipcRenderer.invoke('get_tables', db_name) },
  get_table_headers: (db_name: string, tb_name: string) => { return ipcRenderer.invoke('get_table_headers', db_name, tb_name) },
  get_table_contents: (tb_header: string[], tb_name: string) => { return ipcRenderer.invoke('get_table_contents', tb_header, tb_name) }
})