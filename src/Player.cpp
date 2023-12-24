#include "Player.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

Player::Player(string path_to_animtaion, shared_ptr <GameSound> game_sound, sf::Vector2f spawn_pos) : Entity(path_to_animtaion, 500) {
	heal = 3;
	this->game_sound = game_sound;
	json config;
	ifstream infile("save.json");
	infile >> config;

	if (config["Weapons"]["number"] > 0) {
		isSecondWeapon = true;
	}
	else {	
		isSecondWeapon = false;
	}
	//isSecondWeapon = true;
	sprite.setScale(1, 1);
	sprite.setColor(Color(255, 255, 255));
	collider.setSize(Vector2f(54, 108));
	collider.setOrigin(27, 54);
	collider.setPosition(spawn_pos);
	groudPoint.setSize(Vector2f(28, 10));
	groudPoint.setOrigin(14, 5);
	groudPoint.setFillColor(Color::Red);
	first_pos = collider.getPosition();
	delta_pos = Vector2f(50, 50);

}
void Player::gravitation(float time) {
	if (is_dash) {
		gravitry = 0.0;
	}
	else {
		if (onGround) {
			gravitry = null_gravity;
		}
		else {
			if (dash_is_over) {
				gravitry = null_gravity;
				dash_is_over = false;
			}
			else {
				gravitry += 0.35;
			}
		}
	}

	if (jumptime < 0) {
		collider.move(0, gravitry * time);
	}
	else {
		collider.move(0, gravitry * time * -1);
	}
}

void Player::jump()
{
	jumptime = 0.75;
	game_sound->stop(4);
	game_sound->play(4);
	//game_sound->play(2);
}

int Player::getHeal() {
	return this->heal;
}

Vector2f Player::getPosition() {
	return collider.getPosition();
}
void Player::damage() {
	heal--;
	invulnerable = true;
	invulnerable_time = 1;
	game_sound->stop(8);
	game_sound->play(8);
}

void Player::control(float delta_time, Event& event){
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::C) {
			if (!is_dash) {
				if (!is_duck_var) {
					if (isSecondWeapon) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
							direction.y = 1;
						}
						else {
							direction.y = 0;
						}
						bullets.push_back(*(new Bullet(Vector2f(collider.getPosition().x, collider.getPosition().y - 27), direction, "Image/Converge.jpg")));
					}
					else {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
							direction.y = 1;
						} else {
							direction.y = 0;
						}
						bullets.push_back(*(new Bullet(Vector2f(collider.getPosition().x, collider.getPosition().y - 27), direction, "Image/CrackedCrackshot.jpg")));
					}
					
					current_animation = "Shoot";
				}
				else {
					current_animation = "Duck Shooting";
					if (isSecondWeapon) {
						bullets.push_back(*(new Bullet(Vector2f(collider.getPosition().x, collider.getPosition().y - 50), sf::Vector2i(direction.x, 0), "Image/Converge.jpg")));
					} else {
						bullets.push_back(*(new Bullet(Vector2f(collider.getPosition().x, collider.getPosition().y - 50), sf::Vector2i(direction.x, 0), "Image/CrackedCrackshot.jpg")));
					}
				}
				is_shooting = true;
				shooting_time = 0.5;

				if (isSecondWeapon) {
					game_sound->stop(2);
					game_sound->stop(6);
					game_sound->play(6);
					game_sound->game_sounds[5].setVolume(30);
				}
				else {
					game_sound->stop(2);
					game_sound->stop(6);
					game_sound->play(2);
					game_sound->game_sounds[2].setVolume(30);
				}
			}
		} else if (event.key.code == Keyboard::LShift && !is_duck_var) {
			is_shooting = false;
			if (dash_time < -1) {
				game_sound->stop(9);
				game_sound->play(9);
				is_dash = true;
				dash_time = animation_speed * ((float)texture_frames["Dash"].size()-3);
				current_animation = "Dash";
			}
		}
	} 

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (onGround) {
			jump();
		}
	}
}

void Player::update(float delta_time, Event& event) {
	
	if (!is_shooting) {
		current_animation = "Idle";
	}
	else {
		if (direction.y) {
			current_animation = "Up Shoot";
		} else {
			current_animation = "Shoot";
		}
	}

	if (!is_dash) {
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			direction.x = 1;
			if (!is_duck_var) {
				if (is_shooting) {
					current_animation = "Run Shooting";
				} else {
					current_animation = "Run";
				}
				if (onGround) {
					collider.move(1000 * delta_time, 0);
				}
				else {
					collider.move(500 * delta_time, 0);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			direction.x = 0;
			if (!is_duck_var) {
				if (is_shooting) {
					current_animation = "Run Shooting";
				}
				else {
					current_animation = "Run";
				}
				if (onGround) {
					collider.move(-1000 * delta_time, 0);
				}
				else {
					collider.move(-500 * delta_time, 0);
				}
			}
		}
	}

	if (onGround) {
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (!is_duck_var) {
				collider.setPosition(collider.getPosition().x, collider.getPosition().y + 50);
				collider.setSize(Vector2f(108, 50));
				save_position();
			}
			is_duck_var = true;
		}
		else {
			if (is_duck_var) {
				collider.setPosition(collider.getPosition().x, collider.getPosition().y - 60);
				collider.setSize(Vector2f(54, 108));
				save_position();
			}
			is_duck_var = false;
		}
	}
	for (Bullet& bullet_iter : bullets) {
		bullet_iter.update(delta_time);
	}
	jumptime -= delta_time;
	dash_time -= delta_time;

	if (dash_time < 0) {
		sprite.setColor(Color(255, 255, 255, 255));
		is_dash = false;
		dash_is_over = true;
	}
	else {
		sprite.setColor(Color(255, 255, 255, 215));
		current_animation = "Dash";
		if (onGround) {

			if (direction.x) {
				collider.move(1000 * delta_time, 0);
			}
			else {
				collider.move(-1000 * delta_time, 0);

			}
		}
		else {
			if (direction.x) {
				collider.move(1000 * delta_time, 0);
			}
			else {
				collider.move(-1000 * delta_time, 0);
			}
		}
		
	}

	if (!onGround) {
		current_animation = "Jump";
		if (is_dash) {
			current_animation = "Dash";
		}
	}
	else {
		if (is_duck_var) {
			current_animation = "Duck";
			if (is_shooting) {
				current_animation = "Duck Shooting";
			}
		}
	}

	second_pos = collider.getPosition();
	if (second_pos.x - first_pos.x != delta_pos.x) {
		delta_pos = second_pos - first_pos;
	} else {
		if (second_pos.y - first_pos.y == 0) {
			if (direction.x) {
				collider.setPosition(collider.getPosition().x - 54, collider.getPosition().y);
			} else {
				collider.setPosition(collider.getPosition().x + 54, collider.getPosition().y);
			}
		}
	}

	shooting_time -= delta_time;
	if (shooting_time < 0) {
		is_shooting = false;
	}

	invulnerable_time -= delta_time;
	if (invulnerable_time < 0.0) {
		sprite.setColor(sf::Color(255, 255, 255, 255));
		invulnerable = false;
	} else {
		sprite.setColor(sf::Color(255, 255, 255, 100));
	}

	first_pos = second_pos;
	sprite.setPosition(Vector2f(collider.getPosition().x, collider.getPosition().y - 10));
	groudPoint.setPosition(Vector2f(collider.getPosition().x, collider.getPosition().y + collider.getLocalBounds().height - 55));
	if (collider.getPosition().y > 23 * 54) {
		damage();
	}
}

bool Player::getInvulnerablity() {
	return invulnerable;
}

bool Player::is_duck(){
	return is_duck_var;
}

void Player::setOnGround(bool ONGround)
{
	this->onGround = ONGround;
}

void Player::nearDoor(bool near_door)
{
	this->near_door = near_door;
}
