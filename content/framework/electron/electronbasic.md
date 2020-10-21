---
title: "Electron Basic"
metaTitle: "Electron Basic"
metaDescription: "This is the meta description for this page"
---

## 일렉트론 이란?

Electron은 Native 어플리케이션이며 Chromium과 Node.js를 1개의 런타임으로  
통합하여 javascript, Html, Css만으로 데스크톱 어플리케이션을 만들 수 있게 해주는 프레임워크입니다.  
&nbsp;  

#### Native 어플리케이션이란?

특정한 플랫폼이나 디바이스를 이용하기 위해 개발된 소프트웨어 프로그램으로서,  
우리가 흔하게 말하는 어플리케이션을 의미합니다.  

## 간단한 어플리케이션 만들어보기

1. node js 설치 여부 확인
일렉트론은 node.js를 필요로 하기 때문에 설치되어 있는지 먼저 확인합니다.

```
node -v
npm -v
```

2. 일렉트론 프로젝트 만들기

```
mkdir my-electron-app && cd my-electron-app
npm init -y
npm i --save--dev electron
```

3. 기본 스크립트 파일 만들기

`main.js`는 메인 프로세스를 실행할 Electron 어플리케이션의 `entry point`가 됩니다.

```js
const { app, BrowserWindow } = require('electron')

function createWindow () {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true
    }
  })

  win.loadFile('index.html')
  win.webContents.openDevTools()
}

app.whenReady().then(createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow()
  }
})
```

#### 코드 분석

- 1 행 : 먼저 패키지 의 app및 BrowserWindow모듈 을 가져 와서 electron애플리케이션의 수명주기 이벤트를 관리하고 브라우저 창을 만들고 제어 할 수 있습니다.
- 3 행 : 그런 다음 노드 통합이 활성화 된 새 브라우저 창 을 만들고이 창 에 index.html파일을 로드 (12 행, 나중에 파일에 대해 설명 함)하고 개발자 도구 (13 행)를 여는 함수를 정의합니다 .
- 16 행 : createWindowElectron 애플리케이션 이 초기화 되면 함수 를 호출하여 새 브라우저 창을 만듭니다 .
- 18 행 : 열려있는 창이 더 이상 없을 때 애플리케이션을 종료하는 새 리스너를 추가합니다. 이 리스너는 운영 체제의 창 관리 동작 으로 인해 macOS에서 작동하지 않습니다 .
- 24 행 : 애플리케이션이 활성화 된 후 표시되는 창이없는 경우에만 새 브라우저 창을 만드는 새 리스너를 추가합니다. 예를 들어, 처음으로 애플리케이션을 실행 한 후 또는 이미 실행중인 애플리케이션을 다시 실행 한 후.

4. `index.html` 웹페이지 만들기

어플리케이션이 초기화되면 표시하려는 웹페이지입니다.  
이 웹 페이지는 렌더러 프로세스를 나타냅니다.  
여러 브라우저 창을 만들 수 있으며 각 창은 자체 독립 렌더러를 사용합니다.  
각 창은 `nodeIntegration` 기본 설정을 통해 Node.js API에 대한 전체 액세스 권한을 선택적으로 부여 할 수 있습니다 .

```html
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Hello World!</title>
    <meta http-equiv="Content-Security-Policy" content="script-src 'self' 'unsafe-inline';" />
</head>
<body>
    <h1>Hello World!</h1>
    We are using node <script>document.write(process.versions.node)</script>,
    Chrome <script>document.write(process.versions.chrome)</script>,
    and Electron <script>document.write(process.versions.electron)</script>.
</body>
</html>
```

5. `package.json` 파일 수정

Electron 애플리케이션은 `package.json`파일을 기본 `entry point`로 사용합니다 (다른 Node.js 애플리케이션처럼). 애플리케이션의 기본 스크립트는 `main.js`이므로 `package.json`을 아래와 같이 수정합니다.  

```json
{
    "name": "my-electron-app",
    "version": "0.1.0",
    "main": "main.js"
}
```
> 참고 : main필드가 생략 된 경우 Electron `index.js`은 `package.json`을 포함하는 디렉토리에서 파일 로드를 시도합니다 .
&nbsp;  

다음 `npm start` 스크립트를 아래와 같이 만듭니다.

```json
{
    "name": "my-electron-app",
    "version": "0.1.0",
    "main": "main.js",
    "scripts": {
        "start": "electron ."
    }
}
```