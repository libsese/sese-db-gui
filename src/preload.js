import {contextBridge, ipcRenderer} from "electron";

contextBridge.exposeInMainWorld("windowApi", {
  minimize: () => {
    ipcRenderer.send("window-min");
  },
  maximize: () => {
    ipcRenderer.send("window-max");
  },
  close: () => {
    ipcRenderer.send("window-close");
  },
})