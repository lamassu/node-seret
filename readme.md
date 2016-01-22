# node-seret

Capturing images from USB(UVC) webcam on linux machines.

Notes by Angel Leon (January 2016):

I've made the module compatible with V8 4.x's new API on Jan 21st 2016.

I added `configure.sh` scripts for Ubuntu, both for 32 and 64 bits architectures.

If you want to build for 32bits, just point the symlinks of `binding.gyp` and `configure.sh` to their 32bit versions.

Then just do the following.

# do this once only to install dependencies
$ ./configure.sh

# and then this to build
$ npm install

If you want to build from a clean slate, just remove the generated build folder and invoke `npm install` again.

## Requirements

- node == 0.10.33
- video4linux2 headers
- c and c++ compiler with `-std=c11` and `-std=c++11`
    - gcc >= 4.7

## Install

On linux machines:

```bash
'Pull the latest i386 build of libturbojpeg and install it'
http://sourceforge.net/projects/libjpeg-turbo/files/

```

For more detail see: examples/*.js (required "pngjs" or native "png" modules)

## API

Initializing API

- `var cam = new v4l2camera.Camera(device)`
- `cam.formats`: Array of available frame formats
- `var format = cam.formats[n]`
    - `format.formatName`: Name of pixel format. e.g. `"YUYV"`
    - `format.format`: ID number of pixel format
    - `format.width`: Frame width
    - `format.height`: Frame height
    - `format.interval.numerator` and `format.interval.denominator`
      : Capturing interval per `numerator/denominator` seconds 
      (e.g. 30fps is 1/30)
- `cam.configSet(format)`
  : Set capture `width`, `height`, `interval` per `numerator/denominator` sec
  if the members exist in the `format` object
- `cam.configGet()` : Get a `format` object of current config

Capturing API

- `cam.start()`
- `cam.stop(afterStoped())`
    - call re-`config(format)` or re-`start()` in `afterStoped()` callback
- `cam.capture(afterCaptured)`: Do cache a current captured frame
    - call `cam.toRGB()` in `afterCaptured(true)` callback
- `cam.toYUYV()`: Get the cached frame as 8bit int Array of pixels YUYVYUYV...
- `cam.toRGB()`: Get the cached frame as 8bit int Array of pixels RGBRGB...
- `cam.device`
- `cam.width`
- `cam.height`

Control API

- `cam.controls`: Array of the control information
- `cam.controlGet(id)`: Get int value of the control of the `id`
  (id is one of cam.controls[n].id)
- `cam.controlSet(id, value)`: Set int value of the control of the `id`
- `var control = cam.controls[n]`: Control spec
    - `control.id`: Control `id` for controlGet and controlSet
    - `control.name`: Control name string
    - `control.type`: `"int"`, `"bool"`, `"button"`, `"menu"` or other types
    - `control.max`, `control.min`, `control.step`: value should be
      `min <= v` and `v <= max` and `(v - min) % step === 0`
    - `control.default`: default value of the control
    - `control.flags`: Several bool flags of the controls
    - `control.menu`: Array of items. 
      A control value is the index of the menu item when type is `"menu"`.

## Build for Development (Updated September 2015)

On linux machines:

The instructions have been updated to ensure this module can be built as of September 1st, 2015.

```bash
'Ensure we use the correct V8 build version (Do Once)'
'Configuration fixes for libturbojpeg (Do Once)'
npm install -g n
n 0.10.33
sudo apt-get install libx32gcc-4.8-dev
sudo apt-get install libc6-dev-i386
sudo apt-get install linux-libc-dev:i386
sudo apt-get install gcc-4.9-multilib g++-4.9-multilib


cd myproject
mkdir -p node_modules
cd node_modules
git clone https://github.com/bitstopco/node-seret.git
cd node-seret
export CFLAGS='-m32'
export CXXFLAGS='-m32'
export LDFLAGS='-m32'
npm install
cd ../..
```

"build/Release/seret.node" is exist after the build.

## Tested Environments

- Ubuntu raring armhf on BeagleBone Black with USB Buffalo BSW13K10H
- Ubuntu raring amd64 on Acer Aspire One with its screen facecam
- Mint linux i5 virtual machine on Lenovo Z570

## Notes

This is a nice resource for understanding how v4l2 works: http://www.jayrambhia.com/blog/capture-v4l2/

## Licenses

[MIT](http://opensource.org/licenses/MIT) and 
[LGPL-3.0](http://opensource.org/licenses/LGPL-3.0) dual
