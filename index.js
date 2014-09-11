'use strict';

var cam = require('./build/Release/seret');
var fd = null;
var buffer = null;
var width = null;
var height = null;

exports.startCapture = function startCapture(device, newBuffer, newWidth, newHeight) {
  width = newWidth;
  height = newHeight;
  buffer = newBuffer;
  fd = cam.cameraOn(device, width, height);
  cam.startCapture(fd);
};

exports.stopCapture = function stopCapture() {
  cam.stopCapture(fd);
  cam.cameraOff(fd);
  fd = null;
  width = null;
  height = null;
  buffer = null;
};

exports.captureFrame = function captureFrame() {
  cam.captureFrame(fd, buffer);
};
