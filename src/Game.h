#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <exception>
#include <fstream>

#include "GameMenu.h"
#include "Save.h"
#include "LevelChoise.h"
#include "Weapons.h"
#include "Settings.h"
#include "Records.h"
#include "GameSound.h"
#include "AssetManager.h"

using namespace std;
using namespace sf;

class Game {
public:

	Game() = default;

	void run();

	Music menu_music;
};