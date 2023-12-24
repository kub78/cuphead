#pragma once
#include "Enemy.h"

class Target : public Enemy {
public:
	Target(sf::Vector2f spawnPose);
};