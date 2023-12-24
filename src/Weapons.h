#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

//#include "Weapons_choise.h"
#include "Save.h"
#include "AssetManager.h"
#include "GameState.h"

using namespace std;
using namespace sf;

class Weapons : public GameState
{

public:
	Weapons(shared_ptr <RenderWindow> window, shared_ptr <Save> save);

	int run();

	int getWeapon() {
		return (*save)("Weapons", "number");
	}

private:
	shared_ptr <Save> save;
};

