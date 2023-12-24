#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

using namespace std;
using namespace sf;
class AnimObject {
protected:
	Image image;
	Texture texture;
	Sprite sprite;
	float current_frame_time = 0, animation_speed = 0;
	size_t current_frame = 0;
	Vector2i direction;

	string current_animation;
	json config;

	bool texture_rect_mode;
	map<string, vector<sf::Texture>> texture_frames;
public:
	map<string, vector<IntRect>> frames;

	AnimObject(string path_to_sprite, string path_to_config, string current_animation, float animation_speed);
	AnimObject(string path_to_animation, string current_animation, float animation_speed);
	void play_animation(float delta_time);
};