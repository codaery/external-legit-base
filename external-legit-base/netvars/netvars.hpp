#pragma once
#include "../includes.hpp"

struct netvar_online {
public:
	uintptr_t get_netvars(std::string var, const char* offset_url_list);
	void initialize(const char* offset_url_list);
};