#pragma once
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Save.h"
#include "GameSound.h"
#include "GameState.h"

using namespace std;
using namespace sf;

class Settings : public GameState
{
public:
	Settings(shared_ptr <RenderWindow> window, shared_ptr<GameSound> game_sound);
	int run();
private:
	shared_ptr<GameSound> game_sound;
};
