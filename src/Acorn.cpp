#include "Acorn.h"
#include <iostream>

Acorn::Acorn(sf::Vector2f spawnPose) : Enemy("Image/Acorn", 0.15) {
	heal = 3;
	type = Enemies::ACORN;
	sprite.setScale(0.75, 0.75);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(81, 108));
	collider.setOrigin(27, 54);
	collider.setPosition(spawnPose);
}