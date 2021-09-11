#pragma once
#include "../includes.hpp"

class engine : public singleton <engine> {
public: 
	DWORD get_localplayer();
	DWORD get_entity_from_index(int index);
	int get_max_players();
	bool is_in_game();
	void force_jump();
	void force_attack();
	float get_sensitivity();
	void set_sensitivity(float sens);
	void reset_sensitivity();
	void set_angles(vector3 angles);
	std::string get_game_dir();
	bool mouse_enabling(bool v);

	int get_csgo_client_version();
private:
	float default_sensitivity = get_sensitivity();
};