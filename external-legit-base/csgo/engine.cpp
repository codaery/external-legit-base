#include "engine.hpp"

DWORD engine::get_localplayer()
{
	return mem::get().rpm<DWORD>(mem::get().client_dll + offsets::local_player);
}

DWORD engine::get_entity_from_index(int index)
{
	return mem::get().rpm<DWORD>(mem::get().client_dll + offsets::entity_list + (index * 0x10));
}

int engine::get_max_players()
{
	return mem::get().rpm<int>(offsets::client_state + offsets::clientstate_maxplayer);
}

int engine::get_csgo_client_version()
{
	return mem::get().rpm<int>((DWORD)mem::get().engine_dll + 0x1B2FA9); // maybe this is outdate
}

std::string engine::get_game_dir()
{
	static std::array< char, 0x120 > game_directory;

	mem::get().read_into(mem::get().engine_dll + offsets::game_directory, 
		game_directory.data(), game_directory.size());

	return std::string(game_directory.data()).append("\\");
}

bool engine::mouse_enabling(bool v)
{
	return mem::get().wpm<bool>(v, mem::get().client_dll + 0xD91E18); // dwMouseEnable
}

float engine::get_sensitivity()
{
    int sensitivity_ptr = mem::get().rpm<int>(mem::get().client_dll + offsets::sensetivity_ptr);
    int sensitivity = mem::get().rpm<int>(mem::get().client_dll + offsets::sensetivity);

    sensitivity ^= sensitivity_ptr;

    float sens = *reinterpret_cast<float*>(&sensitivity);

    return sens;
}

void engine::set_sensitivity(float sens)
{
    int sensitivity_ptr = mem::get().rpm<int>(mem::get().client_dll + offsets::sensetivity_ptr);
    int sensitivity = *reinterpret_cast<int*>(&sens) ^ sensitivity_ptr;

    mem::get().wpm<int>(sensitivity, mem::get().client_dll + offsets::sensetivity);
}

void engine::reset_sensitivity()
{
    set_sensitivity(default_sensitivity);
}

void engine::force_attack()
{
	mem::get().wpm<int>(6, mem::get().client_dll + offsets::force_attack);
}

bool engine::is_in_game()
{
	return mem::get().rpm<int>(offsets::client_state + offsets::clientstate_state) == 6;
}

void engine::force_jump()
{
	mem::get().wpm<int>(6, mem::get().client_dll + offsets::force_jump);
}

void engine::set_angles(vector3 angles)
{
	mem::get().wpm<vector3>(angles, offsets::client_state + offsets::viewangles);
}