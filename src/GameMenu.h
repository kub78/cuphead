#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <chrono>
#include <thread>
#include <fstream>
#include <exception>
#include <memory>
#include <fstream>
#include <vector>

#include "LevelChoise.h"
#include "Weapons.h"
#include "Records.h"
#include "Settings.h"
#include "Save.h"
#include "GameSound.h"
#include "GameState.h"

using namespace sf;
using namespace std;

class GameMenu : public GameState {
public:

	GameMenu(shared_ptr <RenderWindow> window, shared_ptr<GameSound> game_sound);

	int run() override;

	//GameMenu(RenderWindow& windwow, float menux, float menuy, String name[], int sizeFont = 60, int step = 80);

private:
	
	shared_ptr<GameSound> game_sound;

};
