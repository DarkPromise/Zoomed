#ifndef GUI_H
#define GUI_H

#include <string>
#include <GL\glew.h>   //For LoadTGA GLuint, unless I change LoadTGA to unsigned int
#include "LoadTGA.h"
#include "MeshBuilder.h"
#include "Vector3.h"

enum GUI_TYPE
{
	GUI_ITEMBORDER,
	GUI_FEARBORDER,
	GUI_FEAR,
	GUI_SANITY,
	GUI_WRONG,
	GUI_EVENT
};

class Gui
{
public:
	Gui(std::string guiName, const char * imagePath);
	~Gui(void);

	Mesh* getMesh();
	std::string toString();

	void setPosition(Vector3 position);
	Vector3 getPosition();

private:
	std::string m_UIName;
	Mesh * m_GUIMesh;
	Vector3 m_GUIPos;
};

#endif