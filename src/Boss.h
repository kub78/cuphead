#pragma once
#include "Enemy.h"

class Boss : public Enemy {
public:
	Boss(sf::Vector2f spawn_pos);
};