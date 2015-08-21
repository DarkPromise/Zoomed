#include "Sound.h"
Sound::Sound()
{
	sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
	BGM[BGM_NULL] = sound->addSoundSourceFromFile("/sound/complete.mp3", ESM_AUTO_DETECT, true);
}

Sound::~Sound()
{

}

void Sound::PlayBGM(BACKGROUND_MUSIC bgm, Vector3 loc) 
{
	sound->play3D(BGM[bgm], vec3df(loc.x, loc.y, loc.z), false);
}

void Sound::PlayFX(SOUND_FX fx, Vector3 loc)
{
	sound->play3D(Sfx[fx], vec3df(loc.x, loc.y, loc.z), false);
}