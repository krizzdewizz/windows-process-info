# windows-process-info

Fetch Windows process info like cwd, title, command line using Node.js.

## Usage

```js
if (process.platform === 'win32') {

  var getProcessInfo = require('windows-process-info');

  getProcessInfo(process.pid, info => {
    console.log(info);
  });
}
```
