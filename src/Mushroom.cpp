#include "Mushroom.h"
#include <iostream>

Mushroom::Mushroom(sf::Vector2f spawnPose) : Enemy("Image/Murderous Mushroom", 0.15) {
	heal = 2;
	type = Enemies::MUSHROOM;
	sprite.setScale(0.5, 0.5);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(54, 54));
	collider.setOrigin(27, 27);
	collider.setPosition(spawnPose);
	groudPoint.setSize(Vector2f(10, 10));
	groudPoint.setOrigin(5, 5);
	groudPoint.setFillColor(Color::Red);
}