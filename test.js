if (process.platform === 'win32') {

  var getProcessInfo = require('.');

  getProcessInfo(process.pid, info => {
    console.log(info);
  });
}

