#pragma once
#include "../includes.hpp"

namespace utils {
	void attach_console();
	int is_in_insecure();
	void panic_regulate();
	void hide_current_console();
	bool is_console_visible();
	void set_exe_random_name(char* chars);
}