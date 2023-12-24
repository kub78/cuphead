#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include "Save.h"
#include "AssetManager.h"
#include "GameState.h"

using namespace std;
using namespace sf;

class Records : public GameState
{
public:
	Records(shared_ptr <RenderWindow> window, shared_ptr <Save> save);

	int run();

private:
	shared_ptr <Save> save;
};
