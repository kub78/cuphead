#include "Settings.h"

Settings::Settings(shared_ptr <RenderWindow> window, shared_ptr<GameSound> game_sound) : GameState(window), game_sound(game_sound) {}

int Settings::run()
{
	//Settings->clear();
	//RenderWindow Settings(VideoMode::getDesktopMode(), "Settings", Style::Fullscreen);
	//Settings.requestFocus();
	//return 0;
	RectangleShape background_opt(Vector2f(1920, 1080));

	background_opt.setTexture(&AssetManager::GetTexture("Image/cuphead_settings.png"));
	
	Text settings;
	settings.setFont(AssetManager::GetFont("font/font_menu.otf"));
	Text music;
	music.setFont(AssetManager::GetFont("font/font_menu.otf"));
	setParametrs(settings, 750, 50, "Settings", 150, Color(237, 147, 0), 3);
	setParametrs(music, 750, 350, (game_sound->getOnOffSound() ? "Music on" : "Music off"), 150, Color(237, 147, 0), 3);
	while (window->isOpen())
	{
		Event event_opt;
		while (window->pollEvent(event_opt))
		{
			if (event_opt.type == Event::Closed) return -1;
			if (event_opt.type == Event::KeyPressed)
			{
				if (event_opt.key.code == Keyboard::Escape) return 0;

				if (event_opt.key.code == Keyboard::Enter) {
					game_sound->OnOffSound();
					if (game_sound->getOnOffSound()) { 
						music.setString("Music on");
					}
					else music.setString("Music off");
				}
			}
		}
		window->clear();
		window->draw(background_opt);
		window->draw(settings);
		window->draw(music);
		window->display();
	}
	return -1;
}
