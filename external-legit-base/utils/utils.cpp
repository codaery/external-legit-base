#include "utils.hpp"
#include "../csgo/engine.hpp"

void utils::attach_console() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

int utils::is_in_insecure() {
	int result;

	if (std::strstr(GetCommandLineA(), "-insecure"))
		result = 1;
	else
		result = 0;

	return result;
}

void utils::panic_regulate() {
	int res = 0;
	bool panic_k = GetAsyncKeyState(VK_DELETE);

	if (!res && panic_k) {
		engine::get().reset_sensitivity();
		ExitProcess(EXIT_SUCCESS);
	}
}

void utils::hide_current_console() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

bool utils::is_console_visible() {
	return IsWindowVisible(GetConsoleWindow()) != 0;
}

void utils::set_exe_random_name(char* chars) {

	TCHAR szExeFileName[MAX_PATH];
	GetModuleFileName(NULL, szExeFileName, MAX_PATH);
	std::string path = std::string(szExeFileName);
	std::string exe = path.substr(path.find_last_of("\\") + 1, path.size());

	srand(time(0));
	char newname[17];

	int z = rand() % 5 + 5;
	for (int i = 0; i < z; i++)
	{
		char x = chars[rand() % 36];
		newname[i] = x;
	}
	newname[z] = 0x0;
	strcat_s(newname, ".exe\0");

	rename(exe.c_str(), newname);
}