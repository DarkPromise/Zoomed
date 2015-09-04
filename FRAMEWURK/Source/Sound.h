#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

class Sound
{
public:
	Sound();
	~Sound();

	int getNoiseLevel()
	{
		return this->noiseLevel;
	}

	void setNoiseLevel(int noiseLevel)
	{
		this->noiseLevel= noiseLevel;
	}

	void updateNoiseLevel(int noise)
	{
		this->noiseLevel += noise;
	}

	void Update(double dt);

	static void Walking();

	static void MechIn();
	static void MechOut();
	static void MechOnHit();

private:
	int noiseLevel;
	float noiseDelay;
};


#endif