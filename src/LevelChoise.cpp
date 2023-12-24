#include "LevelChoise.h"

LevelChoise::LevelChoise(shared_ptr <RenderWindow> window, shared_ptr <Save> save, shared_ptr <GameSound> game_sound) : GameState(window), save(save),game_sound(game_sound) {
	ifstream in("save.json");
	in >> json_reader;
	if (json_reader["OpenLevels"]["level 1"]) {
		if (json_reader["OpenLevels"]["level 2"]) {
			max_menu = 3;
			name_menu = { "Training level", "Level 1", "Level 2" };
		} else {
			max_menu = 2;
			name_menu = { "Training level", "Level 1" };
		}
	}
	else {
		max_menu = 1;
		name_menu = { "Training level" };
	}

}

int LevelChoise::run()
{

	RectangleShape background_opt(Vector2f(1920, 1080));
	Texture texture_levels;
	//if (!texture_levels.loadFromFile("Image/Cuphead_levels.jpg")) exit(2);

	Text level_choise;
	level_choise.setFont(AssetManager::GetFont("font/font_menu.otf"));
	setParametrs(level_choise, 820, 50, "Levels", 150, Color(237, 147, 0), 3);

	mainMenu.resize(max_menu);

	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step) {
		setInitText(mainMenu[i], name_menu[i], menu_X, ypos);
		mainMenu[i].setFont(AssetManager::GetFont("font/font_menu.otf"));
	}

	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(Color::Red);

	alignMenu(2);

	background_opt.setTexture(&AssetManager::GetTexture("Image/Cuphead_levels.jpg"));
	while (window->isOpen())
	{
		Event event_opt;
		while (window->pollEvent(event_opt))
		{
			if (event_opt.type == Event::Closed) return -1;
			if (event_opt.type == Event::KeyReleased)
			{
				
				if (event_opt.key.code == Keyboard::Up) { moveUp(); }
				if (event_opt.key.code == Keyboard::Down) { moveDown(); }
				if (event_opt.key.code == Keyboard::Escape) return 0;
				if (event_opt.key.code == Keyboard::Return) {
					//cout << "Test " << endl;
					Level level(mainMenuSelected,window,game_sound);
					level.run();
					game_sound->stop(1);
					game_sound->play(0);
				}
			}
		}
		window->clear();
		window->draw(background_opt);
		window->draw(level_choise);
		draw();
		window->display();
	}
	return -1;
}



