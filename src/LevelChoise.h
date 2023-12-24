#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Save.h"
#include "AssetManager.h"
#include "GameState.h"
#include "GameSound.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace sf;

class LevelChoise: public GameState
{
public:
	LevelChoise(shared_ptr <RenderWindow> window, shared_ptr <Save> save, shared_ptr <GameSound> game_sound);
	nlohmann::json json_reader;
	int run() override;
private:
	shared_ptr <GameSound> game_sound;
	shared_ptr <Save> save;
};

