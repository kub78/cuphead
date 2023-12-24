#include "LevelCoin.h"

LevelCoin::LevelCoin(std::string path_to_sprite, std::string path_to_config, Vector2f spawn_pos) : AnimObject(path_to_sprite, path_to_config, "round", 0.20) {
	sprite.setPosition(spawn_pos);
	sprite.setScale(0.5, 0.5);
}

FloatRect LevelCoin::get_local_bounds()
{
	return sprite.getGlobalBounds();
}

void LevelCoin::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
