#include "tools.hpp"

intptr_t scan(const char* pattern, const char* mask, char* begin, unsigned size) {
	unsigned patternLength = strlen(mask);

	for (unsigned i = 0; i < size - patternLength; i++) {
		bool found = true;

		for (unsigned j = 0; j < patternLength; j++) {
			if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j)) {
				found = false;
				break;
			}
		}

		if (found) return ((intptr_t)begin + i);
	}

	return 0;
}

void tools::call_move_mouse(vector3 target, int width, int height) {
	INPUT Input = { 0 };

	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;

	Input.mi.dx = target.x - width / 2;
	Input.mi.dy = target.y - height / 2;

	SendInput(1, &Input, sizeof(INPUT));
}

int tools::set_cursor_position(int32_t x, int32_t y) {
	return SetCursorPos(x, y);
}

auto tools::find_signature(char* pattern, char* mask, char* begin, intptr_t size) {
	char* match{ nullptr };
	SIZE_T bytesRead;
	DWORD oldprotect;
	char* buffer{ nullptr };
	MEMORY_BASIC_INFORMATION mbi;
	mbi.RegionSize = 0x1000;

	VirtualQueryEx(mem::get().process_handle, (LPCVOID)begin, &mbi, sizeof(mbi));

	for (char* current = begin; current < begin + size; current += mbi.RegionSize) {
		if (!VirtualQueryEx(mem::get().process_handle, (LPCVOID)current, &mbi, sizeof(mbi))) continue;
		if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

		delete[] buffer;
		buffer = new char[mbi.RegionSize];

		if (VirtualProtectEx(mem::get().process_handle, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect)) {
			ReadProcessMemory(mem::get().process_handle, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
			VirtualProtectEx(mem::get().process_handle, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

			intptr_t internal_addr = scan(pattern, mask, buffer, bytesRead);

			if (internal_addr != 0) {
				match = current + (internal_addr - (intptr_t)buffer);
				break;
			}
		}
	}

	delete[] buffer;
	return match;
}