#include "Level.h"
#include <chrono>

Level::Level(int level_number, shared_ptr<RenderWindow> window, shared_ptr <GameSound> game_sound) : window(window), level_number(level_number), save(save),game_sound(game_sound) {
	//window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(144);
	level_number = level_number;
	camera.reset(FloatRect(540,0,1920, 1080));

	loadFromFile("level" + to_string(level_number) + ".txt");

	door_texture.loadFromFile("Image/door.png");
	door_sprite.setTexture(door_texture);
	door_sprite.setOrigin(door_sprite.getLocalBounds().width / 2, door_sprite.getLocalBounds().height/2 - 50);
	construct();

	tex_lvl.loadFromFile("Image/level_background_" + to_string(level_number) + ".png");
	lvl_sprite.setTexture(tex_lvl);
	lvl_sprite.setPosition(0, 54); 

	interface_load.loadFromFile("Image/interface_coin.png");
	interface_load.createMaskFromColor(sf::Color(255, 255, 255));
	tcoin_bar.loadFromImage(interface_load);
	coin_bar.setTexture(tcoin_bar);
	coin_bar.setTextureRect(sf::IntRect(3, 3, 118, 118));
	coin_bar.setScale(0.5, 0.5);


	font.loadFromFile("C:/Windows/Fonts/Comicz.ttf");

	ifstream in("save.json");
	in >> json_reader;
	in.close();
	coins = json_reader["Coins"]["coins"];

	coin_count.setString("x" + to_string(coins));
	coin_count.setCharacterSize(48);
	coin_count.setFillColor(sf::Color::Magenta);
	coin_count.setFont(font);
	
	heal_count.setString("HP");
	heal_count.setCharacterSize(48);
	heal_count.setFillColor(sf::Color::Black);
	heal_count.setOutlineThickness(3);
	heal_count.setOutlineColor(sf::Color::White);
	heal_count.setFont(font);
	
	shade.setSize(sf::Vector2f(1920, 1080));
	shade.setOrigin(1920/2, 1080/2);
	shade.setFillColor(Color::Black);

	tlose_text.loadFromFile("Image/lose_text.png");
	lose_text.setTexture(tlose_text);
	lose_text.setTextureRect(sf::IntRect(1, 1, 1078, 234));
	lose_text.setOrigin(1078 / 2, 234 / 2);

	twin_text.loadFromFile("Image/victory_text.png");
	win_text.setTexture(twin_text);
	win_text.setTextureRect(sf::IntRect(3, 1447, 1279, 2160 - 1447));
	win_text.setOrigin(1279 / 2, (2160 - 1445) / 2);
	
	timer_ui.setFont(font);
	timer_ui.setCharacterSize(64);
	timer_ui.setFillColor(sf::Color::Black);
	timer_ui.setOutlineThickness(3);
	timer_ui.setOutlineColor(sf::Color::White);
	timer_ui.setString("00.00");
	timer_ui.setOrigin(timer_ui.getLocalBounds().width / 2, timer_ui.getCharacterSize() / 2);

	global_timer = std::chrono::duration<double>(0);

}

void Level::leave() {
	camera.setCenter(960, 540);
	window->setView(camera);
	game_sound->stop(2);
	game_sound->stop(3);
	game_sound->stop(4);
	game_sound->stop(5);
	game_sound->stop(10);
	game_sound->stop(11);
}

int Level::run() {
	auto last_time = chrono::high_resolution_clock::now();
	chrono::duration<double> time;
	Clock clock;

	game_sound->stop(0);
	switch (level_number) {
	case 0:
		game_sound->play(1);
		game_sound->game_sounds[1].setVolume(10);
		break;
	case 1:
		game_sound->play(10);
		game_sound->game_sounds[10].setVolume(10);
		break;
	default:
		game_sound->play(11);
		game_sound->game_sounds[11].setVolume(10);
		break;
	}
	
	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed) {
				return 0;
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Escape) { 
					leave();
					return 0;
				}
			}

			this->player->control(time.count(), event);
		}
		auto current_time = chrono::high_resolution_clock::now();
		time = current_time - last_time;
		last_time = current_time;

		if (!is_lose) {
			this->player->update(time.count(), event);

			player->play_animation(time.count());
		
			if (player->getPosition().x < level_size * 54 - 1920/2) {
				if (player->getPosition().x < 1920/2) {
					camera.setCenter(1920 / 2 + 27, 621);
				} else {
					camera.setCenter(player->get_position().x, 621);
				}
			}
		

			if (player->get_global_bounds().intersects(door_sprite.getGlobalBounds())) {
				double result = stod(std::to_string(global_timer.count()).substr(0, std::to_string(global_timer.count()).find('.') + 3));
				ifstream in("save.json");
				in >> json_reader;
				in.close();
				json_reader["Coins"]["coins"] = coins;
				ofstream out("save.json");
				out << json_reader;
				out.close();

				if (level_number == 1) {
					ifstream in("save.json");
					in >> json_reader;
					in.close();
					json_reader["OpenLevels"]["level 2"] = true;
					in.close();
					if (json_reader["Records"]["level 1"] > global_timer.count() || json_reader["Records"]["level 1"] < 1) {
						json_reader["Records"]["level 1"] = result;
						ofstream out("save.json");
						out << json_reader;
						out.close();
					}
				}
				else if (level_number == 2) {
					ifstream in("save.json");
					in >> json_reader;
					in.close();
					if (json_reader["Records"]["level 2"] > global_timer.count() || json_reader["Records"]["level 2"] < 1) {
						json_reader["Records"]["level 2"] = result;
						ofstream out("save.json");
						out << json_reader;
						out.close();
					}
				}
				else {
					ifstream in("save.json");
					in >> json_reader;
					in.close();
					json_reader["OpenLevels"]["level 1"] = true;
					ofstream out("save.json");
					out << json_reader;
					out.close();
				}
				//camera.setCenter(960, 540);
				//window->setView(camera);
				is_lose = 2;		
			}

			player->setCollide(false);
			for (Element& element_iter : elements) {
				if (player->get_global_bounds().intersects(element_iter.self.getGlobalBounds())) {
					player->setCollide(true);
				}
			}

			if (player->getCollide()) {
				player->update_position();
			}
			else {
				player->save_position();
				player->gravitation(time.count());
			}

			for (Enemy& enemy_iter : enemies) {
				enemy_iter.setCollide(false);
				for (Element& element_iter : elements) {
					if (enemy_iter.get_global_bounds().intersects(element_iter.self.getGlobalBounds())) {
						if (enemy_iter.getType() != ACORN) {
							enemy_iter.setCollide(true);
						}
					}
				}

				if (enemy_iter.getCollide()) {
					enemy_iter.update_position();
				}
				else {
					enemy_iter.save_position();
					if (enemy_iter.getType() == ACORN) {
						if (enemy_iter.isAttack) {
							enemy_iter.gravitation(time.count());
						}
					}
					else if (enemy_iter.getType() == DAISY) {
						if (enemy_iter.isNear) {
							enemy_iter.gravitation(time.count());
						}
					}
					else {
						enemy_iter.gravitation(time.count());
					}
				}
			}

			player->bullets.erase(remove_if(player->bullets.begin(), player->bullets.end(), [&](Bullet& bullet_iter) {
				for (Element& element_iter : elements) {
					if (bullet_iter.self.getGlobalBounds().intersects(element_iter.self.getGlobalBounds()) && !element_iter.isTemporary) {
						game_sound->stop(3);
						game_sound->play(3);
						return true;
					}
				}

				for (int i = 0; i != enemies.size(); i++) {
					if (bullet_iter.self.getGlobalBounds().intersects(enemies[i].get_global_bounds())) {
						if (enemies[i].getType() == Enemies::BOUBLE) {
							enemies[i].sleep();
						}
						else if (enemies[i].getType() == Enemies::TOOTHY) {

						} else {
							if (player->isSecondWeapon) {
								enemies[i].damage();
								enemies[i].damage();
							} else {
								enemies[i].damage();
							}
						}
						if (!enemies[i].getHeal()) {
							enemies[i].kill();
							if (enemies[i].getType() == BOSS || enemies[i].getType() == TARGET) {
								elements.erase(remove_if(elements.begin(), elements.end(), [&](Element &element_iter) {
									return element_iter.isTemporary;
								}), elements.end());
							}
						}
						game_sound->stop(3);
						game_sound->play(3);
						return true;
					}
				}

				return false;
				}), player->bullets.end());

			for (Enemy& enemy_iter : enemies) {
				if ((player->get_global_bounds().intersects(enemy_iter.get_global_bounds()) && !player->getInvulnerablity())) {
					if (enemy_iter.getType() == Enemies::BOUBLE && enemy_iter.isAttack) {

					} else {
						player->damage();
					}
				}
				if (level_number) {
					enemy_iter.attack(time.count(), player->getPosition());
				}
				if (enemy_iter.getType() == BOSS) {
					if (enemy_iter.isAttack) {
						enemies.push_back(*(new Acorn(sf::Vector2f(enemy_iter.get_position().x, enemy_iter.get_position().y))));
					}
				}
			}

			for (LevelCoin& coin : level_coins) {
				coin.play_animation(time.count());
			}

			heal_count.setPosition(camera.getCenter().x - 900, camera.getCenter().y + 440);
			timer_ui.setPosition(camera.getCenter().x, camera.getCenter().y - 520);

			coin_bar.setPosition(camera.getCenter().x - 750, camera.getCenter().y + 440);
			coin_count.setPosition(camera.getCenter().x - 700, camera.getCenter().y + 440);
			level_coins.erase(remove_if(level_coins.begin(), level_coins.end(), [&](LevelCoin& coin_iter) {
				if (coin_iter.get_local_bounds().intersects(player->get_global_bounds())) {
					coins++;
					coin_count.setString("x" + to_string(coins));
					return true;
				}

				return false;
				}), level_coins.end());
			heal_count.setString("HP " + std::to_string(player->getHeal()));
			if (player->getHeal() == 3) {
				heal_count.setFillColor(sf::Color::Green);
			}
			else if (player->getHeal() == 2) {
				heal_count.setFillColor(sf::Color(165, 255, 0));
			}
			else if (player->getHeal() == 1) {
				heal_count.setFillColor(sf::Color::Red);
			} else {
				is_lose = 1;
			}

		


			window->setView(camera);
			window->clear(Color::Black);
			window->draw(lvl_sprite);

			for (Element& element_iter : elements) {
				window->draw(element_iter.self);
			}
			window->draw(door_sprite);
			for (LevelCoin& coin : level_coins) {
				coin.draw(*window);
			}

			for (Enemy& enemy_iter : enemies) {
				enemy_iter.update(time.count(), player->getPosition());
				enemy_iter.play_animation(time.count());

				enemy_iter.bullets.erase(remove_if(enemy_iter.bullets.begin(), enemy_iter.bullets.end(), [&](const Bullet& bullet_iter) {
					for (Element& element_iter : elements) {
						if (bullet_iter.self.getGlobalBounds().intersects(element_iter.self.getGlobalBounds())) {
							return true;
						}
						if (bullet_iter.self.getGlobalBounds().intersects(player->get_global_bounds())) {
							player->damage();
							return true;
						}
					}
					return false;
				}), enemy_iter.bullets.end());
				
				enemy_iter.draw(*window);
			}
			global_timer += time;
			timer_ui.setString(std::to_string(global_timer.count()).substr(0, std::to_string(global_timer.count()).find('.') + 3));
		} else if (is_lose == 1) {
			if ((int)lose_time == 5) {
				game_sound->AllStop();
				game_sound->play(7);
				lose_time -= 1.0;
			}
			
			lose_time -= time.count();
			if (lose_time < 0.0) {
				leave();
				return 0;
			}
		}
		else {
			if ((int)lose_time == 5) {
				game_sound->AllStop();
				game_sound->play(5);
				lose_time -= 1.0;
			}

			lose_time -= time.count();
			if (lose_time < 0.0) {
				leave();
				return 0;
			}
		}

		player->draw(*window);
		
		window->draw(heal_count);
		if (level_number) {
			window->draw(timer_ui);
		}
		window->draw(coin_bar);
		window->draw(coin_count);
		
		if (is_lose) {
			shade.setPosition(camera.getCenter());
			window->draw(shade);
			if (is_lose == 1) {
				lose_text.setPosition(camera.getCenter());
				window->draw(lose_text);
			}
			else {
				win_text.setPosition(camera.getCenter());
				window->draw(win_text);
			}
		}

		window->display();
	}
	return 0;
}

void Level::loadFromFile(string filename)
{
	string buffer;
	ifstream file(filename);
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, buffer);
			level_map.push_back(buffer);
		}
	}
	level_size = level_map[0].size() - 2;
}

void Level::construct()
{
	for (int i = 0; i != level_map.size(); i++) {
		for (int k = 0; k != level_map[i].size(); k++) {
			if (level_map[i][k] == 'g') {
				if (level_number == 0) {
					elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "Ground")));
				}
				else if (level_number == 1) {
					elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "Grass")));
				}
				else {
					elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "level3_ground")));
				}
			}
			if (level_map[i][k] == 'o') {
				elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "dirt")));
			}
			if (level_map[i][k] == 'w') {
				elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "wood")));
			}
			if (level_map[i][k] == 'b') {
				if(level_number == 0) {
				 	elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "block")));
				}
				else {
					elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "box")));
				}
			}
			else if (level_map[i][k] == 'z') {
				elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "Block")));
			}
			else if (level_map[i][k] == '0') {
				elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "Barier")));
			}
			else if (level_map[i][k] == '1') {
				elements.push_back(*(new Element(Vector2f(k * 54, i * 54), "Barier")));
				elements[elements.size() - 1].isTemporary = true;
			}
			else if (level_map[i][k] == 's') {
				player = new Player("Image/cuphead", game_sound, Vector2f(k * 54, i * 54));
			} else if (level_map[i][k] == 'c') {
				level_coins.push_back(*(new LevelCoin("Image/level_coin.png", "Config/coin-config.json", sf::Vector2f(k * 54, i * 54))));
			}
			else if (level_map[i][k] == 'd') {
				door_sprite.setPosition(k * 54, i * 54);
			}
			else if (level_map[i][k] == 'M') {
				enemies.push_back(*(new Mushroom(sf::Vector2f(k * 54, i * 54))));
			}
			else if (level_map[i][k] == 'D') {
				enemies.push_back(*(new Daisy(sf::Vector2f(k * 54, i * 54))));
			}
			else if (level_map[i][k] == 'A') {
				enemies.push_back(*(new Acorn(sf::Vector2f(k * 54, i * 54))));
			}
			else if (level_map[i][k] == 'B') {
				enemies.push_back(*(new Bouble(sf::Vector2f(k * 54, i * 54))));
			} else if (level_map[i][k] == 'T') {
				enemies.push_back(*(new Toothy(sf::Vector2f(k * 54, i * 54))));
			} else if (level_map[i][k] == 'L') {
				enemies.push_back(*(new Target(sf::Vector2f(k * 54, i * 54))));
			} else if (level_map[i][k] == 'P') {
				enemies.push_back(*(new Boss(sf::Vector2f(k * 54, i * 54))));
			}
		}
	}
}
