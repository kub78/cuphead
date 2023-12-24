#include "Bouble.h"
#include <iostream>

Bouble::Bouble(sf::Vector2f spawnPose) : Enemy("Image/Bouble", 0.15) {
	heal = 3;
	type = Enemies::BOUBLE;
	sprite.setScale(0.75, 0.75);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(54, 54));
	collider.setOrigin(27, 27);
	collider.setPosition(spawnPose);
	groudPoint.setSize(Vector2f(10, 10));
	groudPoint.setOrigin(5, 5);
	groudPoint.setFillColor(Color::Red);
}