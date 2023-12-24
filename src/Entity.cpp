#include "Entity.h"

Entity::Entity(string path_to_animation, float speed) : AnimObject(path_to_animation, "Idle", 0.09) {
	collider.setSize(Vector2f(0, 0));
	collider.setFillColor(Color::Blue);
	speed = speed;
}

bool Entity::getCollide() {
	return collide;
}

void Entity::setCollide(bool isCollide) {
	collide = isCollide;
}

void Entity::set_collider(Vector2f size){
	collider.setSize(size);
}

void Entity::update(float delta_time, Event &event){
}

Vector2f Entity::get_position(){
	return sprite.getPosition();
}

void Entity::save_position(){
	last_pos = collider.getPosition();
	//onGround = false;

}

void Entity::update_position(){
	enemyOnGround = true;
	collider.setPosition(last_pos);
	//onGround = true;
}

void Entity::draw(RenderWindow& window){
	for (Bullet& bullet_iter : bullets) {
		bullet_iter.draw(window);
	}
	window.draw(sprite);
	window.draw(decor);
	//window.draw(groudPoint);
	//if (onGround) {
	//}
}

FloatRect Entity::get_global_bounds() {
	return collider.getGlobalBounds();
}

void Entity::gravitation(float time) {
	if (isAlive) {
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
					gravitry += 0.098;
				}
			}
		}
		if (enemyIsJump) {
			collider.move(0, -gravitry * time);
		} else {
			collider.move(0, gravitry * time);
		}
	}
}

FloatRect Entity::get_groundCollider_bounds()
{
	return groudPoint.getGlobalBounds();
}

void Entity::damage() {
	heal--;
}

int Entity::getHeal() {
	return heal;
}