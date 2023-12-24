#pragma once
#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class Element
{
public:
	bool isTemporary = false;
	Texture texture;
	Sprite self;
	Element(Vector2f posichion,string name);
};

