#include "process.h"

class Handle
{
	HANDLE _h;

  public:
	Handle(HANDLE h) : _h(h) {}
	~Handle()
	{
		if (_h)
		{
			CloseHandle(_h);
		}
	}
};

PVOID getPebAddress(HANDLE processHandle)
{
	fnNtQueryInformationProcess fun = (fnNtQueryInformationProcess)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueryInformationProcess");
	PROCESS_BASIC_INFORMATION pbi;

	fun(processHandle, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);

	return pbi.PebBaseAddress;
}

#define BUFFER_SIZE 1024

string getProcessInfo(int pid, string &outCwd, string &outTitle, string &outCommandLine)
{
	auto processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	Handle toClose(processHandle);

	if (processHandle == 0)
	{
		return "";
	}

	auto pebAddress = getPebAddress(processHandle);

	PVOID processParams;
	if (!ReadProcessMemory(processHandle, (PCHAR)pebAddress + offsetof(PEB, ProcessParameters), &processParams, sizeof(PVOID), NULL))
	{
		return "cannot get process parameters";
	}

	// CurrentDirectoryPath
	{
		UNICODE_STRING s;
		if (!ReadProcessMemory(processHandle, (PCHAR)processParams + offsetof(Q, CurrentDirectoryPath), &s, sizeof(s), NULL))
		{
			return "cannot get directory path";
		}

		WCHAR c[BUFFER_SIZE];
		if (!ReadProcessMemory(processHandle, s.Buffer, c, BUFFER_SIZE, NULL))
		{
			char q[1000];
			sprintf_s(q, 1000, "cannot get directory path contents (%d)", GetLastError());
			return q;
		}

		char buf[BUFFER_SIZE * 2];
		sprintf_s(buf, BUFFER_SIZE * 2, "%.*S\n", s.Length / 2, c);

		outCwd = buf;
	}

	// WindowTitle
	{
		UNICODE_STRING s;
		if (!ReadProcessMemory(processHandle, (PCHAR)processParams + offsetof(Q, WindowTitle), &s, sizeof(s), NULL))
		{
			return "cannot get title";
		}

		WCHAR c[BUFFER_SIZE];
		if (!ReadProcessMemory(processHandle, s.Buffer, c, BUFFER_SIZE, NULL))
		{
			char q[1000];
			sprintf_s(q, 1000, "cannot get title contents (%d)", GetLastError());
			return q;
		}

		char buf[BUFFER_SIZE * 2];
		sprintf_s(buf, BUFFER_SIZE * 2, "%.*S\n", s.Length / 2, c);

		outTitle = buf;
	}

	// CommandLine
	{
		UNICODE_STRING s;
		if (!ReadProcessMemory(processHandle, (PCHAR)processParams + offsetof(Q, CommandLine), &s, sizeof(s), NULL))
		{
			return "cannot get command line";
		}

		WCHAR c[BUFFER_SIZE];
		if (!ReadProcessMemory(processHandle, s.Buffer, c, BUFFER_SIZE, NULL))
		{
			char q[1000];
			sprintf_s(q, 1000, "cannot get command line contents (%d)", GetLastError());
			return q;
		}

		char buf[BUFFER_SIZE * 2];
		sprintf_s(buf, BUFFER_SIZE * 2, "%.*S\n", s.Length / 2, c);

		outCommandLine = buf;
	}

	return "";
}
