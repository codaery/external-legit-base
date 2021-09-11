#include "includes.hpp"
#include "csgo/engine.hpp"

#define netvar_offsets_url "https://github.com/frk1/hazedumper/blob/master/csgo.hpp"
netvar_online* netvars;

int main() {
	utils::set_exe_random_name((char*)"0123456789abcdefghijklmnopqrstuvwxyz");

	mem::get().process_attach("csgo.exe");
	mem::get().client_dll = mem::get().get_module("client.dll");
	mem::get().engine_dll = mem::get().get_module("engine.dll");

	netvars->initialize(netvar_offsets_url);
	Sleep(500);

	while (1) {

		entity_t local_player = engine::get().get_localplayer();

		if (!local_player.is_valid_player())
			return 0;

		if (local_player.get_flash_duration() > 0.f)
			local_player.set_flash_duration(0.2f); // for test

	}
	return 1;
}