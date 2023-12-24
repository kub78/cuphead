#include "Enemy.h"

Enemy::Enemy(string path_to_animation, float speed) : Entity(path_to_animation, speed) {
	isAlive = true;
	tdecor.loadFromFile("Image/decor.png");
	decor.setTexture(tdecor);
	decor.setOrigin(decor.getLocalBounds().width/2, decor.getGlobalBounds().height/2);
}

void Enemy::projectile() {
	switch (type) {
	case Enemies::MUSHROOM:
		bullets.push_back(*(new Bullet(collider.getPosition(), sf::Vector2i(!direction.x, direction.y), "Image/mushroom_cloud.png")));
		isAttacked = true;
		shootTime = 1.5;
		break;
	}
}

void Enemy::jump() {
	if (!isAttack) {
		isAttack = true;
		attackTime = 2.5;
		enemyIsJump = true;
	}
}

void Enemy::attack(double delta_time, sf::Vector2f player_pos) {
	if (isAlive) {
		switch (type) {
		case Enemies::MUSHROOM:
			if (isAlive) {
				if (abs(player_pos.x - collider.getPosition().x) < 400) { //&& abs(player_pos.y - collider.getGlobalBounds().top + 200) < collider.getLocalBounds().height) {
					isAttack = true;
					attackTime = animation_speed * texture_frames["Attack"].size();
				}
				else {
					shootTime = 0;
					current_animation = "Idle";
				}
			}
			break;
		case Enemies::DAISY:
			if (direction.x) {
				if (enemyOnGround) {
					collider.move(-600 * delta_time, 0);
				}
				else {
					collider.move(-100 * delta_time, 0);
				}
			}
			else {
				if (enemyOnGround) {
					collider.move(600 * delta_time, 0);
				}
				else {
					collider.move(100 * delta_time, 0);
				}
			}
			break;
		case Enemies::ACORN:
			if (abs(collider.getPosition().x - player_pos.x) < 200) {
				attackTime += delta_time;
			}
			else {
				attackTime = 0;
			}
			if (attackTime > 2) {
				isAttack = true;
			}

			if (isAttack) {
				current_animation = "Fall";
			}
			if (collider.getPosition().y > 23 * 54) {
				kill();
			}
			break;
		case Enemies::BOUBLE:
			if (player_pos.x - collider.getPosition().x > 0) {
				direction.x = 0;
			}
			else {
				direction.x = 1;
			}
			break;
		case Enemies::TOOTHY:
			if (enemyOnGround) {
				if (abs(player_pos.x - collider.getPosition().x) < 400) {
					jump();
				}
			}
			break;
		case Enemies::BOSS:
			if (attackTime < 0.0) {
				if (abs(collider.getPosition().x - player_pos.x) < 1920) {
					isAttack = true;
					attackTime = 7;
				}
			}
			attackTime -= delta_time;
			decor.setPosition(collider.getPosition().x, collider.getPosition().y - 250);
			break;
		}
	}
}

void Enemy::sleep() {
	attackTime = texture_frames["Melt"].size() * animation_speed + texture_frames["Unmelt"].size() * animation_speed;
}

void Enemy::update(double delta_time, sf::Vector2f player_pos) {
	if (isAlive) {
		switch (type) {
		case Enemies::MUSHROOM:
			if (player_pos.x - collider.getPosition().x > 0) {
				direction.x = 0;
			}
			else {
				direction.x = 1;
			}

			if (attackTime < 0.0) {
				isAttack = false;
			}
			else {
				if (shootTime < 0.0) {
					projectile();
				}
			}

			if (isAttack) {
				current_animation = "Attack";
			}
			else {
				isAttacked = false;
			}

			attackTime -= delta_time;
			shootTime -= delta_time;


			for (Bullet& bullet_iter : bullets) {
				bullet_iter.update(delta_time);
			}
			break;
		case Enemies::DAISY:
			if (abs(player_pos.x - collider.getPosition().x) < 1920 / 1.5) {
				isNear = true;
			}
			else {
				isNear = false;
			}
			if (player_pos.x - collider.getPosition().x > 0) {
				direction.x = 0;
			}
			else {
				direction.x = 1;
			}

			if (enemyOnGround) {
				current_animation = "Run";
			}
			break;
		case Enemies::ACORN:
			if (onAttackLine) {
				if (player_pos.x - collider.getPosition().x > 0) {
					direction.x = 0;
				}
				else {
					direction.x = 1;
				}

				if (abs(collider.getPosition().x - player_pos.x) < 1920 / 2) {
					if (!isAttack) {
						if (direction.x) {
							if (abs(collider.getPosition().x - player_pos.x) > 54) {
								collider.move(-300 * delta_time, 0);
							}
						}
						else {
							if (abs(collider.getPosition().x - player_pos.x) > 54) {
								collider.move(300 * delta_time, 0);
							}
						}
					}
				}
			} else {
				if (collider.getPosition().y > 54 * 1 && collider.getPosition().y < 54 * 5) {
					onAttackLine = true;
				}
				collider.move(0, -300 * delta_time);
			}
			break;
		case Enemies::BOUBLE:
			if (!isAttack) {
				current_animation = "Idle";
				if (!direction.x) {
					collider.move(500 * delta_time, 0);
				}
				else {
					collider.move(-500 * delta_time, 0);
				}
			}
			else {
				if (attackTime > texture_frames["Unmelt"].size() * animation_speed) {
					current_animation = "Melt";
				}
				else {
					current_animation = "Unmelt";
				}
			}

			if (attackTime > 0.0) {
				isAttack = true;
			}
			else {
				isAttack = false;
			}

			attackTime -= delta_time;
			break;
		case Enemies::TOOTHY:
			attackTime -= delta_time;
			if (attackTime < 0.0) {
				enemyIsJump = false;
			}
			if (collider.getPosition().y > 26 * 54) {
				isAttack = false;
			}
			break;
		}
		if (collider.getPosition().y > 23 * 54 && type != Enemies::TOOTHY) {
			kill();
		}
	}
	if (type == Enemies::BOUBLE && isAttack) {
			sprite.setPosition(collider.getPosition().x, collider.getPosition().y + 20);
	} else {
		sprite.setPosition(collider.getPosition().x, collider.getPosition().y);
	}

	if (type == Enemies::TOOTHY) {
		groudPoint.setPosition(collider.getPosition().x, collider.getPosition().y + 54);
	} else {
		groudPoint.setPosition(collider.getPosition().x, collider.getPosition().y + 27);
	}
}


void Enemy::draw(sf::RenderWindow& window) {
	if (type == BOSS) {
		isAttack = false;
	}
	for (Bullet& bullet_iter : bullets) {
		bullet_iter.draw(window);
	}
	window.draw(sprite);
	if (attackTime < 7 && attackTime > 5)
	window.draw(decor);
}


int Enemy::getType() {
	return type;
}
void Enemy::kill() {
	decor.setPosition(-1000, -1000);
	bullets.clear();
	collider.setPosition(-1000, -1000);
	isAlive = false;
}