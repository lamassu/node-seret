var fs = require('fs');
var seret = require('./index');

var width = 960;
var height = 720;
var buffer = new Buffer(width * height);

var t0 = Date.now();

seret.startCapture('/dev/video0', buffer, 960, 720);
console.log(Date.now() - t0);
seret.captureFrame();
console.log(Date.now() - t0);
seret.captureFrame();
console.log(Date.now() - t0);
fs.writeFileSync('./result.gray', buffer);
console.log(Date.now() - t0);
seret.stopCapture();
console.log(Date.now() - t0);

seret.startCapture('/dev/video0', buffer, 960, 720);
console.log(Date.now() - t0);
seret.captureFrame();
console.log(Date.now() - t0);
seret.captureFrame();
console.log(Date.now() - t0);
fs.writeFileSync('./result2.gray', buffer);
console.log(Date.now() - t0);
seret.stopCapture();
console.log(Date.now() - t0);
