#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include "Vector3.h"

struct Animation
{
	Animation() {}

	void Set(int startFrame, int endFrame, int repeat, float time, bool active = true)
	{
		this->startFrame = startFrame; 
		this->endFrame = endFrame;
		this->repeatCount =	repeat; 
		this->animTime = time;
		this->playing = active;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
	bool playing;
}; 

class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();

	void resetAnimation();

	void pause();
	void unpause();

	int m_row;
	int m_col;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
}; 

#endif