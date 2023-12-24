#pragma once
#include "Save.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class Weapons_choise
{
	shared_ptr <Save> save;
	bool Fireballs = true;
	bool Watershot = false;

public:

	Weapons_choise(shared_ptr <Save> save) : save(save) {}
	bool OnOffFireball()
	{
		return (*save)("Weapons", "Fireballs");
	}

	bool OnOffWatershot()
	{
		return (*save)("Weapons", "Watershot");
	}

};

