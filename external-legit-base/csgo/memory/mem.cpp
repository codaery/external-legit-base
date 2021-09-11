#include "mem.hpp"
#include <TlHelp32.h>

bool mem::process_attach(const char* process_name)
{
	PROCESSENTRY32 procEntry32;
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcSnap == INVALID_HANDLE_VALUE)
		return false;

	if (Process32First(hProcSnap, &procEntry32))
	{
		if (!strcmp(process_name, procEntry32.szExeFile))
		{
			process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			if (!process_handle) {
				CloseHandle(hProcSnap);
				return false;
			}

			process_id = procEntry32.th32ProcessID;

			CloseHandle(hProcSnap);
			return true;
		}
	}

	while (Process32Next(hProcSnap, &procEntry32))
	{
		if (!strcmp(process_name, procEntry32.szExeFile))
		{
			process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			if (!process_handle) {
				CloseHandle(hProcSnap);
				return false;
			}

			process_id = procEntry32.th32ProcessID;

			CloseHandle(hProcSnap);
			return true;
		}
	}

	CloseHandle(hProcSnap);
	return false;
}

DWORD mem::get_module(const char* module_name)
{
	HANDLE hSnapShot;
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);

	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(MODULEENTRY32);

	if (hSnapShot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	if (Module32First(hSnapShot, &mEntry))
	{
		if (!strcmp(module_name, mEntry.szModule))
		{
			CloseHandle(hSnapShot);
			return (DWORD)mEntry.modBaseAddr;
		}
	}

	while (Module32Next(hSnapShot, &mEntry))
	{
		if (!strcmp(module_name, mEntry.szModule))
		{
			CloseHandle(hSnapShot);
			return (DWORD)mEntry.modBaseAddr;
		}
	}
	CloseHandle(hSnapShot);
	return false;
}
