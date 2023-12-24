#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"

using namespace std;
using namespace sf;

class GameState
{
public:
	GameState(shared_ptr <RenderWindow> window);
	virtual int run() = 0;
protected:
	void draw();

	void moveUp();

	void moveDown();

	void alignMenu(int posx);

	void setInitText(Text& text, String str, float xpos, float ypos);

	void setParametrs(Text& mtext, float xpos, float ypos, const String& str, int size_font = 60, Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

	float menu_X = 950;
	float menu_Y = 350;
	int menu_Step = 120;
	int max_menu = 0;
	int size_font = 100;
	int mainMenuSelected;
	Font font;
	vector<Text> mainMenu;
	vector <String> name_menu;
	//String name_menu[5]{ "Levels", "Weapon", "Records", "Settings", "Exit" };

	Color menu_text_color = Color(237, 147, 0);
	Color chose_text_color = Color::Red;
	Color border_color = Color::Black;

	shared_ptr <RenderWindow> window;


};

