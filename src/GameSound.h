#pragma once
#include<array>
#include<SFML/Audio.hpp>

#include "AssetManager.h"
#include "Save.h"

using namespace std;
using namespace sf;

const int sound_num = 12;

class GameSound
{
	shared_ptr <Save> save;

public:
	array<Sound, sound_num> game_sounds;
	bool getOnOffSound() const
	{
		return (*save)("Music", "music");
	}

	GameSound(shared_ptr <Save> save) : save(save)
	{
		std::array<std::string, sound_num> namefilebuf{"sound/menu.ogg", "sound/Tutorial.ogg", "sound/blaster.ogg", "sound/player_shoot_hit_06.ogg",
			"sound/player_jump_02.ogg", "sound/bravo.ogg","sound/player_weapon_charge_start_005.ogg", "sound/lose.ogg", "sound/damage.ogg", "sound/dash.ogg", "sound/first-level.ogg", "sound/second-level.ogg"};

		for (int i = 0; i < game_sounds.size(); i++) {
			game_sounds[i].setBuffer(AssetManager::GetSoundBuffer(namefilebuf[i]));
			switch (i) {
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				game_sounds[i].setLoop(false);
				break;
			default:
				game_sounds[i].setLoop(true);
				break;
			}
		}
	};

	void play(int index);
	void stop(int index);
	void OnOffSound();
	void AllStop();
};
