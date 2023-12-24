#include "Boss.h"


Boss::Boss(sf::Vector2f spawnPose) : Enemy("Image/Boss", 0.15) {
	heal = 30;
	direction.x = 1;
	type = Enemies::BOSS;
	sprite.setScale(0.75, 0.75);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(200, 300));
	collider.setOrigin(100, 150);
	collider.setPosition(spawnPose);
}