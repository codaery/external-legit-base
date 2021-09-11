#include "netvars.hpp"

#include <Wininet.h>
#pragma comment( lib, "dwrite.lib" )
#pragma comment( lib, "Dwmapi.lib" )
#pragma comment( lib, "Winmm.lib" )
#pragma comment(lib, "Wininet.lib")

#include <fstream>
#include <sstream>

uintptr_t netvar_online::get_netvars(std::string var, const char* offset_url_list) {

	const auto internet = InternetOpen("browser", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
	const auto internet_address = InternetOpenUrl(internet, offset_url_list, nullptr, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

	char* data = nullptr;
	unsigned long bytes_read = NULL;
	unsigned long data_size = NULL;

	do
	{
		char buffer[2000];
		InternetReadFile(internet_address, reinterpret_cast<LPVOID>(buffer), _countof(buffer), &bytes_read);
		auto* temp_data = new char[data_size + bytes_read];
		memcpy(temp_data, data, data_size);
		memcpy(temp_data + data_size, buffer, bytes_read);
		delete[] data;
		data = temp_data;
		data_size += bytes_read;
	} while (bytes_read);

	auto data_str = std::string(data);
	auto pos_start = data_str.find(var);
	pos_start = data_str.find("0x", pos_start + 1);

	if (pos_start != std::string::npos)
	{

		const auto pos_end = data_str.find_first_of(';', pos_start);
		if (pos_end != std::string::npos)
		{
			const auto addr = data_str.substr(pos_start, pos_end - pos_start);

			uintptr_t return_addr = NULL;
			std::stringstream convert_stream;
			convert_stream << addr;
			convert_stream >> std::hex >> return_addr;

			return return_addr;
		}
	}

	InternetCloseHandle(internet_address);
	InternetCloseHandle(internet);

	return NULL;
}

void netvar_online::initialize(const char* offset_url_list) {

	offsets::local_player = get_netvars("dwLocalPlayer", offset_url_list);
	offsets::entity_list = get_netvars("dwEntityList", offset_url_list);
	offsets::force_attack = get_netvars("dwForceAttack", offset_url_list);
	offsets::force_jump = get_netvars("dwForceJump", offset_url_list);
	offsets::viewmatrix = get_netvars("dwViewMatrix", offset_url_list);
	offsets::client_state = get_netvars("dwClientState", offset_url_list);
	offsets::clientstate_state = get_netvars("dwClientState_State", offset_url_list);
	offsets::clientstate_maxplayer = get_netvars("dwClientState_MaxPlayer", offset_url_list);
	offsets::aim_punch = get_netvars("m_aimPunchAngle", offset_url_list);
	offsets::flags = get_netvars("m_fFlags", offset_url_list);
	offsets::health = get_netvars("m_iHealth", offset_url_list);
	offsets::defusing = get_netvars("m_bIsDefusing", offset_url_list);
	offsets::armor_value = get_netvars("m_ArmorValue", offset_url_list);
	offsets::spotted = get_netvars("m_bSpotted", offset_url_list);
	offsets::game_directory = get_netvars("dwGameDir", offset_url_list);
	offsets::account_id = get_netvars("m_iAccountID", offset_url_list);
	offsets::sensetivity = get_netvars("dwSensitivity", offset_url_list);
	offsets::sensetivity_ptr = get_netvars("dwSensitivityPtr", offset_url_list);
	offsets::flash_duration = get_netvars("m_flFlashDuration", offset_url_list);
	offsets::flash_max_alpha = get_netvars("m_flFlashMaxAlpha", offset_url_list);
	offsets::comp_wins = get_netvars("m_iCompetitiveWins", offset_url_list);
	offsets::has_defuse = get_netvars("m_bHasDefuser", offset_url_list);
	offsets::scoped = get_netvars("m_bIsScoped", offset_url_list);
	offsets::has_helmet = get_netvars("m_bHasHelmet", offset_url_list);
	offsets::team_num = get_netvars("m_iTeamNum", offset_url_list);
	offsets::life_state = get_netvars("m_lifeState", offset_url_list);
	offsets::origin = get_netvars("m_vecOrigin", offset_url_list);
	offsets::viewoffset = get_netvars("m_vecViewOffset", offset_url_list);
	offsets::bone_matrix = get_netvars("m_dwBoneMatrix", offset_url_list);
	offsets::crosshairid = get_netvars("m_iCrosshairId", offset_url_list);
	offsets::dormant = 0xED;
	offsets::viewangles = get_netvars("dwClientState_ViewAngles", offset_url_list);
	offsets::glow_index = get_netvars("m_iGlowIndex", offset_url_list);
	offsets::active_weapon = get_netvars("m_hActiveWeapon", offset_url_list);
	offsets::item_index = get_netvars("m_iItemDefinitionIndex", offset_url_list);
	offsets::current_map_dir = get_netvars("dwClientState_MapDirectory", offset_url_list);

}
