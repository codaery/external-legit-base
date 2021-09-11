#pragma once
#include "../includes.hpp"

class entity_t {
public:
	entity_t(DWORD addy)
	{
		address = addy;
	}

	int get_health();
	int get_class_id();

	bool is_alive();
	bool is_valid_player();

	int get_team();

	bool is_defusing();

	int get_armor();

	bool is_spotted();
	void set_spotted(bool v);

	int get_comp_wins();
	int get_account_id();

	float get_flash_duration();
	float get_flash_max_alpha();
	void set_flash_duration(float duration);

	bool has_kit();
	bool is_scoped();
	bool has_helmet();

	int get_crosshair_id();
	int get_lifestate();
	int get_flags();

	bool is_dormant();

	void aim_to(vector3 to);
	float get_dist_to(vector3 target);

	vector3 get_pos();
	vector3 get_punch();
	vector3 return_bone(vector3 bone, int bone_id);
	vector3 get_eye_position();

	DWORD get_bone_matrix();

	vector3 get_bone_pos(int bone);
	vector3 get_angles();

	DWORD address = 0;
};