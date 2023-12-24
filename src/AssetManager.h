#pragma once

#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <assert.h>
#include<map>

using namespace std;
using namespace sf;

class AssetManager
{
public:
	AssetManager();

	static Texture& GetTexture(const string& filename);
	static SoundBuffer& GetSoundBuffer(const string& filename);
	static Font& GetFont(const string& filename);

private:

	map<string, Texture> m_Textures;
	map<string, SoundBuffer> m_SoundBuffer;
	map<string, Font> m_Fonts;

	static AssetManager* sInstance;
};