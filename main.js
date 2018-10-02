const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow
const path = require('path')



/*************************************************************
 * py process Starting server side scripts
 *************************************************************/
console.log("[+]Starting serverside scripts")
const script = 'core/router.py'
const port = '5000'

const guessPackaged = () => {
  
  return require('fs').existsSync(script)
}

const createPyProc = () => {
  
  if (guessPackaged()) {
    //pyProc = require('child_process').execFile(script)
    pyProc = require('child_process').spawn('python3', [script])
  } 
 
  if (pyProc != null) {
    //console.log(pyProc)
    console.log('child process success on port ' + port)
  }
}

const exitPyProc = () => {
  console.log("[+]Closing the Server....")
  pyProc.kill()
  pyProc = null
  pyPort = null
}

app.on('ready', createPyProc)
app.on('will-quit', exitPyProc)


/*************************************************************
 * Screen management
 *************************************************************/

let mainWindow = null

const createWindow = () => {
  mainWindow = new BrowserWindow({width: 800, height: 600})
  mainWindow.loadURL(require('url').format({
    pathname: path.join(__dirname,'screens', 'login.html'),
    protocol: 'file:',
    slashes: true
  }))
  mainWindow.webContents.openDevTools()
  mainWindow.maximize();

  mainWindow.on('closed', () => {
    mainWindow = null
  })
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})