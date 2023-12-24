#include "GameMenu.h"

GameMenu::GameMenu(shared_ptr<RenderWindow> window,shared_ptr<GameSound> game_sound) : GameState(window), game_sound(game_sound)
{
	max_menu = 5;
	name_menu = { "Levels", "Weapon", "Records", "Settings", "Exit" };
}

int GameMenu::run()
{
	ofstream logFile("log.txt", ios_base::app);
	auto width = static_cast<float>(VideoMode::getDesktopMode().width);
	auto height = static_cast<float>(VideoMode::getDesktopMode().height);
	RectangleShape background(Vector2f(width, height));
	Texture texture_window;
	/*if (!texture_window.loadFromFile("Image/Cuphead_mainmenu.jpg")) {
		logFile << "Cant load texture" << endl;
		logFile.close();
		return -1;
	}*/
	background.setTexture(&AssetManager::GetTexture("Image/Cuphead_mainmenu.jpg"));
	//game_sound->getOnOffSound();

	mainMenu.resize(max_menu);
	//mainMenu = new Text[max_menu];
	logFile.close();

	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step) {
		setInitText(mainMenu[i], name_menu[i], menu_X, ypos);
		mainMenu[i].setFont(AssetManager::GetFont("font/font_menu.otf"));
	}

	logFile.close();
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(Color::Red);

	Text Titul;
	Titul.setFont(AssetManager::GetFont("font/font_menu.otf"));
	setParametrs(Titul, 750, 50, "Cuphead", 150, Color(237, 147, 0), 3);
	
	alignMenu(2);

	while (window->isOpen()) {
		Event event;
		while (window->pollEvent(event)) {

			if (event.type == Event::KeyReleased) {

				if (event.key.code == Keyboard::Up) { moveUp(); }
				if (event.key.code == Keyboard::Down) { moveDown(); }
				if (event.key.code == Keyboard::Return)
				{
					if (mainMenuSelected == 4) {
						return -1;
					}
					return mainMenuSelected;
				}
			}
		}
		window->clear();
		window->draw(background);
		window->draw(Titul);
		draw();
		window->display();
	}
	return -1;
}

