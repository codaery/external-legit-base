#pragma once
#include "../../includes.hpp"
#include <TlHelp32.h>

class mem : public singleton <mem> {
public:
	HWND is_counter_strike_global_offensive = FindWindowA(
		"Valve001", "Counter-Strike: Global Offensive");

	DWORD client_dll = 0;
	DWORD engine_dll = 0;

	int process_id = 0;
	HANDLE process_handle = 0;


	bool process_attach(const char* process_name);
	DWORD get_module(const char* module_name);

	template<typename t>
	bool wpm(t value, DWORD addy);
	template <typename t>
	t rpm(DWORD addy);

	inline bool read_into(const uint32_t& address, void* buffer, const size_t& size);
};

template<typename t>
bool mem::wpm(t value, DWORD addy) {
	return
		WriteProcessMemory(process_handle, (PVOID)addy,
			&value, sizeof(t), 0);
}

template <typename t>
inline t mem::rpm(DWORD addy) {
	t data;
	ReadProcessMemory(process_handle, (PVOID)addy,
		&data, sizeof(t), 0);
	return
		data;
}

inline bool mem::read_into(const uint32_t& address, void* buffer, const size_t& size)
{
	SIZE_T bytes_readed = 0;
	return !!ReadProcessMemory(process_handle, reinterpret_cast<const void*>(address), 
		buffer, size, &bytes_readed);
}

