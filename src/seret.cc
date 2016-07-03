#include <nan.h>

// C standard library
#include <cstdlib>
#include <ctime>
#include <string.h>

#include "camera.h"

NAN_METHOD(CameraOn) {
  if (info.Length() != 4) {
    return Nan::ThrowTypeError("cameraOn requires 4 arguments");
  }

  String::AsciiValue deviceString(info[0].As<v8::Object>());
  uint32_t width = Nan::To<uint32_t>(info[1]);
  uint32_t height = Nan::To<uint32_t>(info[2]);
  uint32_t fps = Nan::To<uint32_t>(info[3]);

  int fd = camera_on(*deviceString, width, height, fps);

  return scope.Close(Integer::New(fd));
}

NAN_METHOD(CameraOff) {
  if (info.Length() != 1) {
    return Nan::ThrowTypeError("cameraOff requires 1 argument");
  }

  int fd = Nan::To<int>(info[0]);

  camera_off(fd);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(StartCapture) {
  if (info.Length() != 1) {
    return Nan::ThrowTypeError("startCapture requires 1 argument");
  }

  int fd = args[0]->IntegerValue();

  int success = 0;
  do {
    success = (0 == start_capturing(fd));
    if (!success) stop_capturing(fd);
  } while (!success);

  return scope.Close(Null());
}

Handle<Value> StopCapture(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 1) {
    return ThrowException(
      Exception::TypeError(String::New("stopCapture requires 1 argument"))
    );
  }

  int fd = args[0]->IntegerValue();

  stop_capturing(fd);

  return scope.Close(Null());
}

Handle<Value> CaptureFrame(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 2) {
    return ThrowException(
      Exception::TypeError(String::New("captureFrame requires 2 arguments"))
    );
  }

  int fd = args[0]->IntegerValue();

  v8::Local<v8::Object> buffer = args[1]->ToObject();
  char* bufferData   = node::Buffer::Data(buffer);
  size_t bufferLength = node::Buffer::Length(buffer);
  int result = capture_frame(fd, bufferData, bufferLength);

  return scope.Close(Integer::New(result));
}

Handle<Value> ControlSet(const Arguments& args) {
  HandleScope scope;

  if (args.Length() != 3) {
    return ThrowException(
      Exception::TypeError(String::New("captureFrame requires 3 arguments"))
    );
  }

  int fd = args[0]->IntegerValue();
  uint32_t id = args[1]->Uint32Value();
  int32_t value = args[2]->Int32Value();

  control_set(fd, id, value);

  return scope.Close(Null());
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("cameraOn").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(CameraOn)).ToLocalChecked());
  Nan::Set(target, Nan::New("cameraOff").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(CameraOff)).ToLocalChecked());
  Nan::Set(target, Nan::New("startCapture").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(StartCapture)).ToLocalChecked());
  Nan::Set(target, Nan::New("stopCapture").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(StopCapture)).ToLocalChecked());
  Nan::Set(target, Nan::New("captureFrame").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(CaptureFrame)).ToLocalChecked());
  Nan::Set(target, Nan::New("controlSet").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(ControlSet)).ToLocalChecked());
}

NODE_MODULE(seret, InitAll);
