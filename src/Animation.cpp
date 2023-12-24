#include "Animation.h"


AnimObject::AnimObject(std::string path_to_sprite, std::string path_to_config, std::string current_animation, float animation_speed) {
	texture_rect_mode = true;
	direction = Vector2i(0, 0);

	this->current_animation = current_animation;
	this->animation_speed = animation_speed;
	
	image.loadFromFile(path_to_sprite);
	image.createMaskFromColor(sf::Color(255, 255, 255));
	image.createMaskFromColor(sf::Color(34, 163, 70));
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	ifstream input(path_to_config);

	if (input.is_open()) {
		input >> config;
		input.close();
	}

	for (auto& element : config.items()) {
		const std::string & animation_name = element.key();
		vector<IntRect> animation_frames;
		for (auto& frame : element.value()) {
			animation_frames.push_back(IntRect(frame[0], frame[1], frame[2], frame[3]));
		}
		frames[animation_name] = animation_frames;
	}
}

AnimObject::AnimObject(string path_to_animation, string current_animation, float animation_speed)
{
	texture_rect_mode = false;
	direction = Vector2i(0, 0);

	this->current_animation = current_animation;
	this->animation_speed = animation_speed;
	for (const auto& folder_entry : boost::filesystem::directory_iterator(path_to_animation)) {
		for (const auto& entry : boost::filesystem::directory_iterator(path_to_animation + "/" + folder_entry.path().filename().string())) {
			sf::Texture texture;
			if (texture.loadFromFile(path_to_animation + "/" + folder_entry.path().filename().string() + "/" + entry.path().filename().string())) {
				texture_frames[folder_entry.path().filename().string()].push_back(texture);
			}
		}
	}
}

void AnimObject::play_animation(float delta_time) {
	current_frame_time += delta_time;

	if (texture_rect_mode) {
		if (current_frame_time > frames[current_animation].size() * animation_speed) {
			current_frame_time = 0;
			current_frame = 0;
		}
	}
	else {
		if (current_frame_time > texture_frames[current_animation].size() * animation_speed) {
			current_frame_time = 0;
			current_frame = 0;
		}
	}

	current_frame = (int)(current_frame_time / animation_speed);

	if (texture_rect_mode) {
		if (direction.x) {
			sprite.setTextureRect(frames[current_animation][current_frame]);
		}
		else {
			IntRect mirrored_rect(frames[current_animation][current_frame]);
			mirrored_rect.left += mirrored_rect.width;
			mirrored_rect.width *= -1;
			sprite.setTextureRect(mirrored_rect);
		}

		if (current_animation != "Duck") {
			sprite.setOrigin(frames[current_animation][current_frame].width / 2, frames[current_animation][current_frame].height / 2);
		}
		else {
			sprite.setOrigin(frames[current_animation][current_frame].width / 2 - 14, frames[current_animation][current_frame].height);
		}
	}
	else {
		sprite.setTexture(texture_frames[current_animation][current_frame]);
		if (direction.x) {
			sprite.setTextureRect(sf::IntRect(0, 0, texture_frames[current_animation][current_frame].getSize().x, texture_frames[current_animation][current_frame].getSize().y));
		}
		else {
			int texture_width = texture_frames[current_animation][current_frame].getSize().x * -1;
			sprite.setTextureRect(sf::IntRect(texture_frames[current_animation][current_frame].getSize().x, 0, texture_width, texture_frames[current_animation][current_frame].getSize().y));
		}
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}
}