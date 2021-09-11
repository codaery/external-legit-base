#include "options.hpp"
#include "../csgo/engine.hpp"

int rndm(int min, int max) {
	return rand() % max + min;
}

auto cs_opt::get_closest_enemy() {
	float closest_distance = rndm(999999, 
		1000000);

	entity_t local_player = engine::get().get_localplayer();
	entity_t closest_enemy = 0;

	int team = local_player.get_team();

	for (size_t i = 0; i <= engine::get().get_max_players(); i++) {
		entity_t entity = engine::get().get_entity_from_index(i);

		if (entity.is_valid_player() && entity.get_team() != team) {

			float distance = local_player.get_dist_to(entity.get_pos());
			if (distance < closest_distance) {
				closest_distance = distance;
				closest_enemy = entity;
			}
		}
	}
	return closest_enemy;
}