const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');

const isDev = !app.isPackaged;

function createWindow() {
  const win = new BrowserWindow({
    width: 1200,
    height: 800,
    backgroundColor: 'white',

    webPreferences: {
      nodeIntegration: false,
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js'),
    },
  });

  win.loadFile('index.html');
}

if (isDev) {
  require('electron-reload')(__dirname, {
    electron: path.join(__dirname, 'node_modules', '.bin', 'electron'),
    ignored: [/\.program/, /\.out/, /\.json/],
  });
}

app.whenReady().then(() => {
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });

  createWindow();
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

const fs = require('fs');
const execSync = require('child_process').execSync;

ipcMain.on('compile', (event, code) => {
  fs.writeFileSync('./input.program', code);

  execSync('compiler.exe < input.program');

  const compiledCode = Buffer.from(fs.readFileSync('./program.out')).toString();
  const symbolTable = JSON.parse(
    Buffer.from(fs.readFileSync('./symbolTable.json')).toString()
  ).slice(1);
  const errors = JSON.parse(Buffer.from(fs.readFileSync('./error.json')).toString()).slice(1);

  event.sender.send('compile-done', {
    code,
    compiledCode,
    symbolTable,
    errors,
  });
});
