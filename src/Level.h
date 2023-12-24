#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Element.h"
#include "Save.h"
#include "GameSound.h"
#include "LevelCoin.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "Daisy.h"
#include "Acorn.h"
#include "Bouble.h"
#include "Toothy.h"
#include "Target.h"
#include "Boss.h"
#include <chrono>
#include <nlohmann/json.hpp>

using namespace std;
using namespace sf;
class Level
{
public:

	Level(int level_number, shared_ptr<RenderWindow> window,shared_ptr <GameSound> game_sound);

	int run();

	void loadFromFile(string filename);
	void leave();
	void construct();

private:
	nlohmann::json json_reader;
	Text timer_ui;
	std::chrono::duration<double> global_timer;
	Texture tex_lvl;
	Sprite lvl_sprite;
	double lose_time = 5;
	int is_lose = 0;
	sf::RectangleShape shade;
	int level_size = 0;

	Texture tlose_text, twin_text;
	Sprite lose_text, win_text;

	int coins = 0;
	std::vector<LevelCoin> level_coins;

	Image interface_load;
	Texture tlife_bar, tcoin_bar;
	Sprite life_bar, coin_bar;

	sf::Font font;
	sf::Text coin_count;
	sf::Text heal_count;

	Texture door_texture;
	Sprite door_sprite;

	shared_ptr <GameSound> game_sound;
	shared_ptr <Save> save;
	Vector2f spawn;
	View camera;
	vector<Element> elements;
	vector<string> level_map;
	vector<RectangleShape> vec;
	shared_ptr<RenderWindow> window;
	int level_number;
	Player *player;

	std::vector<Enemy> enemies;
};

