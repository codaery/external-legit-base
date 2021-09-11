#include "entity.hpp"

int entity_t::get_health()
{
	return mem::get().rpm<int>(address + offsets::health);
}

void entity_t::aim_to(vector3 to)
{
	DWORD client_state = mem::get().rpm<DWORD>(mem::get().engine_dll + offsets::client_state);
	vector3 view_angles = mem::get().rpm<vector3>(client_state + offsets::viewangles);

	vector3 position = get_pos();
	vector3 view_point = get_eye_position();
	vector3 view_pos({ position.x + view_point.x, position.y + view_point.y, position.z + view_point.z });

	vector3 delta({ to.x - view_pos.x, to.y - view_pos.y, to.z - view_pos.z }); 
	float delta_len = (float)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

	float pitch = (float)-asin(delta.z / delta_len) * (180 / (float)M_PI);
	float yaw = (float)atan2(delta.y, delta.x) * (180 / (float)M_PI);

	if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180) {
		view_angles.x = pitch;
		view_angles.y = yaw;
	}

	mem::get().wpm<vector3>(view_angles, client_state + offsets::viewangles);
}

float entity_t::get_dist_to(vector3 target) {
	vector3 local = get_pos();
	return (float)sqrt(pow(target.x - local.x, 2) + pow(target.y - local.y, 2) + pow(target.z - local.z, 2));
}

int entity_t::get_class_id()
{
	return mem::get().rpm<int>(mem::get().rpm<DWORD>(mem::get().rpm<DWORD>(mem::get().rpm<DWORD>(address + 0x8) + 0x8) + 0x1) + 0x14);
}

bool entity_t::is_alive()
{
	return get_health() > 0;
}

bool entity_t::is_valid_player() {
	DWORD health = this->get_health();
	return (health > 0 && health <= 100) && !is_dormant();
}

float entity_t::get_flash_duration() {
	return mem::get().rpm<float>(address + offsets::flash_duration);
}

float entity_t::get_flash_max_alpha() {
	return mem::get().rpm<float>(address + offsets::flash_max_alpha);
}

void entity_t::set_flash_duration(float duration)
{
	mem::get().wpm<float>(duration, address + offsets::flash_duration);
}

int entity_t::get_crosshair_id()
{
	return mem::get().rpm<int>(address + offsets::crosshairid);
}

int entity_t::get_team()
{
	return mem::get().rpm<int>(address + offsets::team_num);
}

bool entity_t::is_defusing()
{
	return mem::get().rpm<bool>(address + offsets::defusing);
}

int entity_t::get_armor()
{
	return mem::get().rpm<int>(address + offsets::armor_value);
}

bool entity_t::is_spotted()
{
	return mem::get().rpm<bool>(address + offsets::spotted);
}

void entity_t::set_spotted(bool v) {
	mem::get().wpm<bool>(v, address + offsets::spotted);
}

int entity_t::get_comp_wins()
{
	return mem::get().rpm<int>(address + offsets::comp_wins);
}

bool entity_t::has_kit()
{
	return mem::get().rpm<bool>(address + offsets::has_defuse);
}

bool entity_t::is_scoped()
{
	return mem::get().rpm<bool>(address + offsets::scoped);
}

bool entity_t::has_helmet()
{
	return mem::get().rpm<bool>(address + offsets::has_helmet);
}

int entity_t::get_lifestate()
{
	return mem::get().rpm<int>(address + offsets::life_state);
}

int entity_t::get_flags()
{
	return mem::get().rpm<int>(address + offsets::flags);
}

bool entity_t::is_dormant()
{
	return mem::get().rpm<bool>(address + offsets::dormant);
}

int entity_t::get_account_id()
{
	return mem::get().rpm<int>(address + offsets::account_id);
}

vector3 entity_t::get_pos()
{
	return mem::get().rpm<vector3>(address + offsets::origin);
}

vector3 entity_t::get_punch() {
	return mem::get().rpm<vector3>(address + offsets::aim_punch);
}

vector3 entity_t::get_eye_position()	
{
	return mem::get().rpm<vector3>(address + offsets::viewoffset);
}

DWORD entity_t::get_bone_matrix()
{
	return mem::get().rpm<DWORD>(address + offsets::bone_matrix);
}

vector3 entity_t::return_bone(vector3 bone, int bone_id) {
	bone.x = mem::get().rpm<float>(get_bone_matrix() + 0x30 * bone_id + 0x0C);
	bone.y = mem::get().rpm<float>(get_bone_matrix() + 0x30 * bone_id + 0x1C);
	bone.z = mem::get().rpm<float>(get_bone_matrix() + 0x30 * bone_id + 0x2C);
	return bone;
}

vector3 entity_t::get_bone_pos(int bone)
{
	vector3 rn_bone;
	return return_bone(rn_bone, bone);
}

vector3 entity_t::get_angles()
{
	return mem::get().rpm<vector3>(offsets::client_state + offsets::viewangles);
}