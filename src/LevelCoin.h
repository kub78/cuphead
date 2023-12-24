#pragma once
#include "Animation.h"
#include <string>

class LevelCoin : public AnimObject {
public:
	LevelCoin(std::string path_to_sprite, std::string path_to_config, Vector2f spawn_pos);
	FloatRect get_local_bounds();
	void draw(sf::RenderWindow &window);
};