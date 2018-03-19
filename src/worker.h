#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

#include <nan.h>
#include "process.h"

class Worker : public Nan::AsyncWorker
{
public:
  Worker(DWORD pid, Nan::Callback *callback);
  ~Worker();

  void Execute();
  void HandleOKCallback();

private:
  DWORD pid;
  string cwd;
  string title;
  string commandLine;
  string error;
};

#endif // SRC_WORKER_H_
