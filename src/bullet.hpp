#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Bullet {
public:
	sf::Vector2i direction;
	float speed = 600;
	RectangleShape self;
	Texture texture;
	Sprite sprite;

	Bullet(Vector2f start_pos,Vector2i direction, string filename);
	void update(float time);
	void draw(RenderWindow& window);
};