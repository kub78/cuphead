#include "bullet.hpp"

Bullet::Bullet(Vector2f start_pos, Vector2i direction, string filename) {
	this->direction = direction;
	texture.loadFromFile(filename);
	self.setTexture(&texture);
	self.setScale(2, 2);
	self.setSize(Vector2f(30, 15));
	self.setOrigin(15, 7);
	self.setPosition(start_pos);
	
	if (!direction.x) {
		if (!direction.y) {
			self.setScale(-2, 2);
		}
	}
	if (direction.y) {
		self.setRotation(-90);
	}
}

void Bullet::update(float time) {
	speed += 0.9;
	if (!direction.y) {
		if (direction.x) {
			self.move(speed * time, 0);
		}
		else {
			self.move(-speed * time, 0);
		}
	} else {
		self.move(0, -speed * time);
	}
}

void Bullet::draw(sf::RenderWindow& window) {

	window.draw(self);

}