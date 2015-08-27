#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "GL\glew.h"
#include "LoadHmap.h"
#include "Player.h"

class Player;

enum CAMERA_MODE { CAMERA_MODE_FIRST, CAMERA_MODE_THIRD, CAMERA_MODE_FREE };

class Camera
{
private:
	CAMERA_MODE m_camera_mode;

public:
	Camera();
	Camera(CAMERA_MODE cm);
	~Camera();

	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;

	Vector3 defaultPos;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 tempStorage;
	Vector3 tempTarget;
	Vector3 tempUp;

	float SPRINT_SPEED;
	std::vector<unsigned char> heightmap;
	Vector3 tScale;

	virtual void setCameraMode(CAMERA_MODE m_camera_mode);
	virtual CAMERA_MODE getCameraMode();

	virtual void UpdateStatus(const unsigned char key); 
	virtual void UpdateJump(const double dt);

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();

	virtual void MoveForward(const double dt); 
	virtual void MoveBackward(const double dt);
	virtual void MoveLeft(const double dt); 
	virtual void MoveRight(const double dt);

	virtual void TurnLeft(const double dt);
	virtual void TurnRight(const double dt);
	virtual void LookUp(const double dt);
	virtual void LookDown(const double dt);
	virtual void SpinClockwise(const double dt);
	virtual void SpinCounterClockwise(const double dt);

	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);
	virtual void Roll(const double dt);
	virtual void Walk(const double dt);
	virtual void Strafe(const double dt);
	virtual void Jump(const double dt);
};

#endif