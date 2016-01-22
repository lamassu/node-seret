#include <v8.h>
#include <node.h>
#include <nan.h>
#include <node_buffer.h>

// C standard library
#include <cstdlib>
#include <ctime>
#include <string.h>

#include "camera.h"

using namespace v8;

void throw_v8_exception(Isolate* isolate, const char* str) {
  isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, str)));
}

void CameraOn(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() != 4) {
    throw_v8_exception(isolate, "CameraOn() takes 4 arguments.");
    return;
  }

  String::Utf8Value deviceString(args[0]->ToString());
  uint32_t width = args[1]->IntegerValue();
  uint32_t height = args[2]->IntegerValue();
  uint32_t fps = args[3]->IntegerValue();
  int fd = camera_on(*deviceString, width, height, fps);
  args.GetReturnValue().Set(Integer::New(isolate, fd));
}

void CameraOff(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() != 1) {
    throw_v8_exception(isolate, "cameraOff requires 1 argument");
    return;
  }

  int fd = args[0]->IntegerValue();
  camera_off(fd);
  args.GetReturnValue().Set(Null(isolate));
}

void StartCapture(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() != 1) {
      throw_v8_exception(isolate,"startCapture requires 1 argument");
      return;
  }

  int fd = args[0]->IntegerValue();

  int success = 0;
  do {
    success = (0 == start_capturing(fd));
    if (!success) stop_capturing(fd);
  } while (!success);

  args.GetReturnValue().Set(Null(isolate));
}

void StopCapture(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);
  if (args.Length() != 1) {
      throw_v8_exception(isolate, "stopCapture requires 1 argument");
      return;
  }
  int fd = args[0]->IntegerValue();
  stop_capturing(fd);
  args.GetReturnValue().Set(Null(isolate));
}

void CaptureFrame(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() != 2) {
      throw_v8_exception(isolate, "captureframe requires 2 arguments");
      return;
  }

  int fd = args[0]->IntegerValue();

  v8::Local<v8::Object> buffer = args[1]->ToObject();
  char* bufferData   = node::Buffer::Data(buffer);
  size_t bufferLength = node::Buffer::Length(buffer);
  int result = capture_frame(fd, bufferData, bufferLength);

  args.GetReturnValue().Set(Integer::New(isolate, result));
}

void ControlSet(const FunctionCallbackInfo<v8::Value>& args) {
  Isolate *isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() != 3) {
      throw_v8_exception(isolate, "controlSet requires 3 arguments");
      return;
  }

  int fd = args[0]->IntegerValue();
  uint32_t id = args[1]->Uint32Value();
  int32_t value = args[2]->Int32Value();
  control_set(fd, id, value);
  args.GetReturnValue().Set(Null(isolate));
}

void RegisterModule(Handle<Object> target) {
  // target is the module object you see when require()ing the .node file.
  NODE_SET_METHOD(target, "cameraOn"    , CameraOn);
  NODE_SET_METHOD(target, "cameraOff"   , CameraOff);
  NODE_SET_METHOD(target, "startCapture", StartCapture);
  NODE_SET_METHOD(target, "stopCapture" , StopCapture);
  NODE_SET_METHOD(target, "captureFrame", CaptureFrame);
  NODE_SET_METHOD(target, "controlSet"  , ControlSet);
}

NODE_MODULE(seret, RegisterModule)
