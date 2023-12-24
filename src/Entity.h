#pragma once
#include "Animation.h"
#include "Save.h"
#include "GameSound.h"
#include "AssetManager.h"
#include "bullet.hpp"
#include <memory>

using namespace std;
using namespace sf;


class Entity : public AnimObject {
protected:
	bool enemyOnGround = false;
	bool isAlive = true;
	bool collide = false;
	bool dash_is_over = true;
	double jumptime = 0; // ����� ���
	double gravitry = 300;
	double dash_cooldown = 0;
	const double null_gravity = 300;
	bool is_jumping = false; // � ����� is_teleporting
	float speed = 0.0;
	Vector2f last_pos;
	RectangleShape collider, groudPoint;
	bool is_dash = false;
	int heal;
	Vector2f first_pos, second_pos;
	Vector2f delta_pos;
public:
	Image idecor;
	Texture tdecor;
	Sprite decor;
	bool enemyIsJump = false;
	bool isSecondWeapon = false;
	bool onGround = true;
	bool getCollide();
	void setCollide(bool isCollide);
	Entity(string path_to_animation, float speed);
	void save_position();
	void update_position();
	FloatRect get_global_bounds();
	void set_collider(Vector2f size);
	virtual void draw(RenderWindow& window);
	virtual void update(float delta_time, Event &event);
	Vector2f get_position();
	virtual void gravitation(float time);
	vector <Bullet> bullets;
	FloatRect get_groundCollider_bounds();
	int getHeal();
	virtual void damage();
};