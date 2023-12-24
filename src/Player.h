#pragma once
#include <memory>

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Save.h"
#include "Weapons.h"
#include "GameSound.h"

class Player : public Entity {
private:
	bool is_duck_var = false;
	bool near_door =  false;
	double dash_time = 0;
	double invulnerable_time = 0.0;
	bool invulnerable = false;
	shared_ptr <GameSound> game_sound;
	double damage_time;
	bool is_shooting = false;
	double shooting_time = 0.0;
public:
	Player(string path_to_animtaion, shared_ptr <GameSound> game_sound, sf::Vector2f spawn_pos);
	void jump();
	int getHeal();
	void control(float delta_time, Event& event);
	void update(float delta_time, Event& event) override;
	bool is_duck();
	void setOnGround(bool ONGround);
	void nearDoor(bool near_door);
	void damage() override;
	bool getInvulnerablity();
	sf::Vector2f getPosition();
	void gravitation(float time) override;
};