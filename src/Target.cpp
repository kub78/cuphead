#include "Target.h"
#include <iostream>

Target::Target(sf::Vector2f spawnPose) : Enemy("Image/Target", 0.15) {
	heal = 3;
	type = Enemies::TARGET;
	direction.x = 1;
	sprite.setScale(2, 2);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(108, 108));
	collider.setOrigin(54, 54);
	collider.setPosition(spawnPose);
	groudPoint.setSize(Vector2f(10, 10));
	groudPoint.setOrigin(5, 5);
	groudPoint.setFillColor(Color::Red);
}