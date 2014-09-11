'use strict';

var fs = require('fs');
var async = require('async');

var cam = require('./build/Release/seret');

var fd = cam.cameraOn('/dev/video0', 960, 720);
var buffer = new Buffer(960 * 720);

var t0 = Date.now();
setInterval(function() { var elapsed = (Date.now() - t0) / 1000; console.log('ping: %d', elapsed); }, 1000);
cam.startCapture(fd);

function captureFrame() {
  cam.captureFrame(fd, buffer);
}

async.timesSeries(100, function(i, next) {
  if (i % 10 === 0) console.log(i);
  captureFrame();
  fs.writeFileSync('./result.gray', buffer);
  setTimeout(next, 10);
}, function() {
  cam.stopCapture(fd);
  cam.cameraOff(fd);
});

