#pragma once
#include "Entity.h"

enum Enemies : int {
	MUSHROOM = 0,
	DAISY = 1,
	ACORN = 2,
	BOUBLE = 3,
	TOOTHY = 4,
	TARGET = 5,
	BOSS = 6
};

class Enemy : public Entity {
protected:
	Enemies type;
	bool onAttackLine = false;
	bool isAttacked = false;
	double attackTime = 0.0;
	double shootTime = 0.0;
	sf::FloatRect player_pos;
	Texture tdecor;
	Sprite decor;
public:
	bool isNear = false;
	bool isAttack = false;
	void sleep();
	Enemy(string path_to_animation, float speed);
	int getType();
	void jump();
	void attack(double delta_time, sf::Vector2f playerPos);
	void kill();
	void projectile();
	void update(double delta_time, Vector2f player_pos);
	void draw(sf::RenderWindow &window) override;
};

