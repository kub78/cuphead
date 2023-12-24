#include "Game.h"

void Game::run() {
	//ofstream out_file("log.txt");
	//out_file << (this->save)("Music", "music") << endl;

	shared_ptr <RenderWindow> window;
	try {
		window = shared_ptr<RenderWindow>(new RenderWindow(VideoMode::getDesktopMode(), L"Cuphead", Style::Fullscreen));


		window->setMouseCursorVisible(false);
	}
	catch (const exception& e) {
		ofstream log_file("log.txt", ios_base::app);
		if (log_file.is_open()) {
			log_file << "Exception: " << e.what() << endl;
			log_file.close();
			return;
		}
	}

	AssetManager asset_manager;
	shared_ptr <Save> save(new Save);
	shared_ptr <GameSound> game_sound(new GameSound(save));

	game_sound->play(0);

	while (true) {
		GameMenu menu(window, game_sound);
		int choice = menu.run();
		switch (choice)
		{
		case 0: {
			LevelChoise level_choise(window,save,game_sound);
			if (level_choise.run() == -1) {
				window->close();
				return;
			}
			break;
		}
		case 1:{
			Weapons weapons_choise(window,save);
			if (weapons_choise.run() == -1) {
				window->close();
				return;
			}
			break;
		}
		case 2: {
			Records records(window, save);
			if (records.run() == -1) {
				window->close();
				return;
		}
			break;
		}
		case 3: {
			Settings settings(window, game_sound);
			if (settings.run() == -1) {
				window->close();
				return;
 			}
			
			break;
		}
		case -1:
			window->close();
			return;

		default:
			break;
		}
	}
}