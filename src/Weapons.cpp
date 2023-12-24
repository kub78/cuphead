#include "Weapons.h"
 
int Weapons::run()
{
	//RenderWindow Weapon(VideoMode::getDesktopMode(), "Weapon", Style::Fullscreen);
	//Weapon.requestFocus();
	//Weapon->clear();
	RectangleShape background_opt(Vector2f(1920, 1080));

	Text weapons;
	weapons.setFont(AssetManager::GetFont("font/font_menu.otf"));
	setParametrs(weapons, 750, 50, "Weapons", 150, Color(237, 147, 0), 3);

	Text Fireballs;
	Text Watershot;
	Fireballs.setFont(AssetManager::GetFont("font/font_menu.otf"));
	Watershot.setFont(AssetManager::GetFont("font/font_menu.otf"));
	if ((*save)("Weapons", "number") == 0) {
		setParametrs(Fireballs, 360, 850,"Selected", 150, Color(237, 147, 0), 3);
		setParametrs(Watershot, 1160, 850,"Not selected", 150, Color(237, 147, 0), 3);
	}
	else if ((*save)("Weapons", "number") == 1) {
		setParametrs(Fireballs, 360, 850, "Not selected", 150, Color(237, 147, 0), 3);
		setParametrs(Watershot, 1160, 850, "Selected", 150, Color(237, 147, 0), 3);
	}
	Texture Crackshot, Converge;
	Sprite crackshot, converge;
	Crackshot.loadFromFile("Image/Crackshot_potion.jpg");
	Converge.loadFromFile("Image/Converge_potion.jpg");
	crackshot.setTexture(Crackshot);
	converge.setTexture(Converge);
	crackshot.setPosition(500, 400);
	crackshot.setScale(2, 2);
	converge.setPosition(1200, 400);
	converge.setScale(2, 2);
	background_opt.setTexture(&AssetManager::GetTexture("Image/cuphead_weapon.jpg"));
	while (window->isOpen())
	{
		Event event_opt;
		while (window->pollEvent(event_opt))
		{
			if (event_opt.type == Event::Closed) return -1;
			if (event_opt.type == Event::KeyPressed)
			{
				if (event_opt.key.code == Keyboard::Escape) return 0;

				if (event_opt.key.code == Keyboard::A) {
					if ((*save)("Weapons", "number") == 1) {
						Fireballs.setString("Selected");
						Watershot.setString("Not selected");
						save->set("Weapons", "number", 0);
					}
				}
				if (event_opt.key.code == Keyboard::D) {
					if ((*save)("Weapons", "number") == 0) {
						Fireballs.setString("Not selected");
						Watershot.setString("Selected");
						save->set("Weapons", "number", 1);
					}
				}
			}
		}
		window->clear();
		window->draw(background_opt);
		window->draw(converge);
		window->draw(crackshot);
		window->draw(weapons);
		window->draw(Fireballs);
		window->draw(Watershot);
		window->display();
	}
	return -1;
}

Weapons::Weapons(shared_ptr <RenderWindow> window, shared_ptr <Save> save) : GameState(window), save(save) {}
