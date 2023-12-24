#include "GameSound.h"

void GameSound::play(int index)
{
	if (game_sounds[index].getStatus() == sf::SoundSource::Status::Stopped && getOnOffSound()) game_sounds[index].play();
}

void GameSound::stop(int index)
{
	if (game_sounds[index].getStatus() == sf::SoundSource::Status::Playing) game_sounds[index].stop();
}

void GameSound::OnOffSound()
{
	if (!getOnOffSound())
	{
		save->set("Music", "music", 1);
		if (game_sounds[0].getStatus() == sf::SoundSource::Status::Stopped) game_sounds[0].play();
	}
	else
	{
		save->set("Music", "music", 0);
		AllStop();
		//for (int i = 0; i < 1; i++) if (game_sounds[i].getStatus() == sf::SoundSource::Status::Playing) game_sounds[i].stop();
	}
}

void GameSound::AllStop()
{
	for (int i = 0; i < game_sounds.size(); i++) if (game_sounds[i].getStatus() == sf::SoundSource::Status::Playing) game_sounds[i].stop();
}