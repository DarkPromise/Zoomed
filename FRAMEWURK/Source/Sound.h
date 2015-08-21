#pragma once
#include <vector>
#include <irrKlang.h>
#include "Vector3.h"

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

enum SOUND_FX
{
	FX_NULL,
	FX_TOTAL
};

enum BACKGROUND_MUSIC
{
	BGM_NULL,
	BGM_TOTAL
};

class Sound
{
public:
	Sound();
	~Sound();

	ISoundEngine* sound;
	ISoundSource* BGM[BGM_TOTAL];
	ISoundSource* Sfx[FX_TOTAL];

	void PlayBGM(BACKGROUND_MUSIC bgm, Vector3 loc);
	void PlayFX(SOUND_FX fx, Vector3 loc);
};
