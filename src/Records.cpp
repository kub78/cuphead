#include "Records.h"

Records::Records(shared_ptr <RenderWindow> window, shared_ptr <Save> save) : GameState(window), save(save) {}

int Records::run()
{
	//RenderWindow Records(VideoMode::getDesktopMode(), "Weapon", Style::Fullscreen);
	//Records.requestFocus();
	//Records->clear();
	RectangleShape background_rec(Vector2f(1920, 1080));
	Text records;
	records.setFont(AssetManager::GetFont("font/font_menu.otf"));
	setParametrs(records, 750, 50, "Records", 150, Color(237, 147, 0), 3);
	background_rec.setTexture(&AssetManager::GetTexture("Image/cuphead_weapon.jpg"));

	Text lvl1, lvl2;
	lvl1.setFont(AssetManager::GetFont("font/font_menu.otf"));
	lvl2.setFont(AssetManager::GetFont("font/font_menu.otf"));
	ifstream in("save.json");
	nlohmann::json json_reader;
	in >> json_reader;

	double rec_lvl1 = json_reader["Records"]["level 1"];
	double rec_lvl2 = json_reader["Records"]["level 2"];

	std::string rez_lvl1 = std::to_string(rec_lvl1).substr(0, std::to_string(rec_lvl1).find('.') + 3);
	std::string rez_lvl2 = std::to_string(rec_lvl2).substr(0, std::to_string(rec_lvl2).find('.') + 3);

	setParametrs(lvl1, 300, 350, "Level 1 -   " + rez_lvl1 + " seconds", 150, Color(237, 147, 0), 3);
	setParametrs(lvl2, 300, 750, "Level 2 -   " + rez_lvl2 + " seconds", 150, Color(237, 147, 0), 3);
	
	while (window->isOpen())
	{
		Event event_opt;
		while (window->pollEvent(event_opt))
		{
			if (event_opt.type == Event::Closed) return -1;
			if (event_opt.type == Event::KeyPressed)
			{
				if (event_opt.key.code == Keyboard::Escape) return 0;
			}
		}
		window->clear();
		window->draw(background_rec);
		window->draw(records);
		window->draw(lvl1);
		window->draw(lvl2);
		window->display();
	}
	return -1;
}


