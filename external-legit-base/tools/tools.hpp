#pragma once
#include "../includes.hpp"

namespace tools {
	void call_move_mouse(vector3 target, int width, int height);
	int set_cursor_position(int32_t x, int32_t y);
	auto find_signature(char* pattern, char* mask, char* begin, intptr_t size);
}