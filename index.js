'use strict';

var cam = require('./build/Release/seret');
var fd = null;
var buffer = null;
var width = null;
var height = null;

// TODO:
// Add JPEG processing
// Stability issues on Nexus7:
// Problem:
// 1. frequent select timeouts
// 2. VIDIOC_STREAMON error 27, File too large
// Possible solutions:
// - allow dynamic adjustment of timeout
// - fswebcam seems more stable, see what it's doing differently
// - after more testing, fswebcam is clearly doing something different
//   this current code has a problem, likely in setup, that's causing
//   the frequent select timeouts while this appears to never happen with
//   fswebcam.
//   try using the src_v4l2.c module from fswebcam and see if the problem goes
//   away. if so, we could either continue using it, or simplify until we find
//   what's causing the issue.
// - also: test just C portion, to see if it's something related to the node addon.
// - update: latest code has been stable so far regarding (1)
// - for (2) catch error, retry

exports.cameraOn = function cameraOn(device, newBuffer, newWidth, newHeight) {
  width = newWidth;
  height = newHeight;
  buffer = newBuffer;
  fd = cam.cameraOn(device, width, height);
};

exports.cameraOff = function cameraOff() {
  cam.cameraOff(fd);
  fd = null;
  width = null;
  height = null;
  buffer = null;
};

exports.startCapture = function startCapture() {
  cam.startCapture(fd);
};

exports.stopCapture = function stopCapture() {
  cam.stopCapture(fd);
};

exports.captureFrame = function captureFrame() {
  var res = cam.captureFrame(fd, buffer);
  return (res === 0);
};

// Note: This must be called either between cameraOn and startCapture
// or immediately after captureFrame
exports.controlSet = function controlSet(id, value) {
  cam.controlSet(fd, id, value);
};
