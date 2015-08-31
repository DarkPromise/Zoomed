#include "Sound.h"


ISoundEngine *sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);


Sound::Sound()
{
	noiseLevel = 0;
	noiseDelay = 0.f;
}

Sound::~Sound()
{

}

void Sound::Update(double dt)
{
	std::cout << noiseLevel << std::endl;
	if (this->noiseLevel > 0)
	{
		noiseDelay += (float)(dt);
		if (noiseDelay > 0.1f)
		{
			noiseDelay = 0.f;
			noiseLevel--;
		}
	}
}

void Sound::Walking()
{
	//sound->play3D("../irrKlang/media/footstep.mp3", vec3df(0,0,0), false);
}