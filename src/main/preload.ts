import {contextBridge, ipcRenderer} from 'electron';

contextBridge.exposeInMainWorld('electronAPI', {
  open_url: (url: string) => ipcRenderer.send('open_url', url)
})