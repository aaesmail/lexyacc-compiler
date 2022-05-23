const { ipcRenderer, contextBridge } = require('electron');

contextBridge.exposeInMainWorld('electron', {
  compile(code) {
    ipcRenderer.send('compile', code);
  },

  onCompileDone(callback) {
    ipcRenderer.on('compile-done', (_, result) => {
      callback(result);
    });
  },
});
