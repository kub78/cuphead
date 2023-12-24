#include "Toothy.h"
#include <iostream>

Toothy::Toothy(sf::Vector2f spawnPose) : Enemy("Image/Toothy", 0.15) {
	heal = 3;
	isAttack = false;
	type = Enemies::TOOTHY;
	sprite.setScale(0.75, 0.75);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(81, 108));
	collider.setOrigin(27, 54);
	collider.setPosition(spawnPose);
	groudPoint.setSize(Vector2f(10, 10));
	groudPoint.setOrigin(5, 5);
	groudPoint.setFillColor(Color::Red);
}