let native = require('../build/Release/windows_process_info.node');

function getProcessInfo(pid, callback) {
  native.getProcessInfo(pid, callback);
}

module.exports = getProcessInfo;
