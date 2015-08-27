#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
public:
	Mouse();
	~Mouse();

	double x, y;
	double last_x, last_y;

	bool m_bLeftButtonPressed;
	bool m_bRightButtonPressed;
};

#endif