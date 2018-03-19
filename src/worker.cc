#include "worker.h"

Worker::Worker(DWORD pid, Nan::Callback *callback)
    : AsyncWorker(callback),
      pid(pid)
{
}

Worker::~Worker()
{
}

void Worker::Execute()
{
  error = getProcessInfo(pid, cwd, title, commandLine);
}

void Worker::HandleOKCallback()
{
  Nan::HandleScope scope;
  v8::Local<v8::Object> object = Nan::New<v8::Object>();
  if (error.empty())
  {
    Nan::Set(object, Nan::New<v8::String>("cwd").ToLocalChecked(), Nan::New<v8::String>(cwd.c_str()).ToLocalChecked());
    Nan::Set(object, Nan::New<v8::String>("title").ToLocalChecked(), Nan::New<v8::String>(title.c_str()).ToLocalChecked());
    Nan::Set(object, Nan::New<v8::String>("commandLine").ToLocalChecked(), Nan::New<v8::String>(commandLine.c_str()).ToLocalChecked());
  }
  else
  {
    Nan::Set(object, Nan::New<v8::String>("error").ToLocalChecked(), Nan::New<v8::String>(error.c_str()).ToLocalChecked());
  }

  v8::Local<v8::Value> argv[] = {object};
  callback->Call(1, argv);
}
