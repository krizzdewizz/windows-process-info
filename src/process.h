#ifndef SRC_PROCESS_H_
#define SRC_PROCESS_H_

#include <nan.h>
#include <windows.h>
#include <Winternl.h>
#include <string>
using namespace std;

typedef struct _Q
{
  ULONG MaximumLength;
  ULONG Length;
  ULONG Flags;
  ULONG DebugFlags;
  PVOID ConsoleHandle;
  ULONG ConsoleFlags;
  HANDLE StdInputHandle;
  HANDLE StdOutputHandle;
  HANDLE StdErrorHandle;
  UNICODE_STRING CurrentDirectoryPath;
  HANDLE CurrentDirectoryHandle;
  UNICODE_STRING DllPath;
  UNICODE_STRING ImagePathName;
  UNICODE_STRING CommandLine;
  PVOID Environment;
  ULONG StartingPositionLeft;
  ULONG StartingPositionTop;
  ULONG Width;
  ULONG Height;
  ULONG CharWidth;
  ULONG CharHeight;
  ULONG ConsoleTextAttributes;
  ULONG WindowFlags;
  ULONG ShowWindowFlags;
  UNICODE_STRING WindowTitle;
  UNICODE_STRING DesktopName;
  UNICODE_STRING ShellInfo;
  UNICODE_STRING RuntimeData;
  //	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} Q, *PQ;

typedef NTSTATUS(NTAPI *fnNtQueryInformationProcess)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL);

string getProcessInfo(int pid, string &outCwd, string &outTitle, string &outCommandLine);

#endif // SRC_PROCESS_H_
