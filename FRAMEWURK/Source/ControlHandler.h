#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

#include "ModelHandler.h"
#include "ViewHandler.h"

#include "timer.h"

class ControlHandler
{
public:
	ControlHandler(ModelHandler * theModel, ViewHandler * theView);
	~ControlHandler(void);

	void RunGameLoop();

	bool ProcessInputs();
	void MouseUpdate();
	void KeyboardUpdate();

	ModelHandler * theModel;
	ViewHandler * theView;

private:
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;
};

#endif
