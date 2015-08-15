#include "Camera.h"
#include "GameApplication.h"
#include "Mtx44.h"

static const float CAMERA_SPEED = 150.f;
static const float MOUSE_SPEED = 30.f;


Camera::Camera()
{
	setCameraMode(CAMERA_MODE_FIRST);
	Reset();
}

Camera::Camera(CAMERA_MODE cm)
{
	setCameraMode(cm);
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPos = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera::Update(const double dt)
{
	if(ViewHandler::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		position += view * CAMERA_SPEED * (float)dt;
		target += view * CAMERA_SPEED * (float)dt;
	}
	if(ViewHandler::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * CAMERA_SPEED  * (float)dt;
		target -= view * CAMERA_SPEED * (float)dt;
	}
	if(ViewHandler::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED * (float)dt;
		target -= right * CAMERA_SPEED * (float)dt;
	}
	if(ViewHandler::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED * (float)dt;
		target += right * CAMERA_SPEED * (float)dt;
	}
}

void Camera::TurnLeft(const double dt)
{

}

void Camera::TurnRight(const double dt)
{

}

void Camera::UpdateJump(const double dt) 
{ 

}

void Camera::Jump(const double dt)
{

}

/****************************************************************************** 
 Move the camera forward 
******************************************************************************/ 
void Camera::MoveForward(const double dt) 
{ 

} 
/****************************************************************************** 
 Move the camera backward 
******************************************************************************/ 
void Camera::MoveBackward(const double dt) 
{ 

} 
/****************************************************************************** 
 Move the camera left 
******************************************************************************/ 
void Camera::MoveLeft(const double dt) 
{ 

} 
/****************************************************************************** 
 Move the camera right 
******************************************************************************/ 
void Camera::MoveRight(const double dt) 
{ 

} 

void Camera::LookUp(const double dt)
{

}

void Camera::LookDown(const double dt)
{
	
}

void Camera::Walk(const double dt)
{

}

void Camera::Strafe(const double dt)
{


}

void Camera::Pitch(const double dt)
{

}

void Camera::Yaw(const double dt)
{

}

void Camera::Roll(const double dt)
{
}

void Camera::SpinClockwise(const double dt)
{
}

void Camera::SpinCounterClockwise(const double dt)
{
}

void Camera::UpdateStatus(const unsigned char key) 
{ 
	ViewHandler::keys[key] = true; 
} 

void Camera::setCameraMode(CAMERA_MODE m_camera_mode)
{
	this->m_camera_mode = m_camera_mode;
}

CAMERA_MODE Camera::getCameraMode()
{
	return m_camera_mode;
}

void Camera::Reset()
{
	position = defaultPos;
	target = defaultTarget;
	up = defaultUp;
	/*ViewHandler::cameraPitch = 0.0;
	ViewHandler::cameraYaw = 0.0;*/
}