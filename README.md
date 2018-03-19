# windows-process-info

Fetch process information for a particular process ID on Windows using Node.js.

## Usage

```js
if (process.platform === 'win32') {

  var getProcessInfo = require('windows-process-info');

  getProcessInfo(process.pid, info => {
    console.log(info);
  });
}
```
