#include <nan.h>
#include "process.h"
#include "worker.h"

void getProcessInfo(const Nan::FunctionCallbackInfo<v8::Value> &args)
{
  if (args.Length() < 2)
  {
    Nan::ThrowTypeError("getProcessInfo expects two arguments.");
    return;
  }

  if (!args[0]->IsNumber())
  {
    Nan::ThrowTypeError("The first argument, pid, must be a number.");
    return;
  }

  if (!args[1]->IsFunction())
  {
    Nan::ThrowTypeError("The second argument, callback, must be a function.");
    return;
  }

  DWORD pid = (DWORD)args[0]->NumberValue();
  Nan::Callback *callback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[1]));
  Nan::AsyncQueueWorker(new Worker(pid, callback));
}

void Init(v8::Local<v8::Object> exports)
{
  exports->Set(Nan::New("getProcessInfo").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(getProcessInfo)->GetFunction());
}

NODE_MODULE(qbert, Init)
