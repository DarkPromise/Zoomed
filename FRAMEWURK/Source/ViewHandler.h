#ifndef VIEW_HANDLER_H
#define VIEW_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //For Windows

#include <GL\glew.h> //GLEW
#include <GLFW/glfw3.h> //GLFW
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Define.h"
#include "ModelHandler.h"
#include "MatrixStack.h"
#include "Geometry.h"
#include "MeshBuilder.h"
#include "LoadOBJ.h"
#include "LoadTGA.h"
#include "Light.h"
#include "Utility.h"
#include "shader.hpp"
#include "Map.h"
#include "Mouse.h"

enum VIEW_TYPE
{
	VIEW_SIDESCROLLER,
	VIEW_2D
};

class ViewHandler
{
public:
	ViewHandler(ModelHandler * theModel);
	~ViewHandler(void);

	BOOL CreateGLWindow(char * title, int m_width, int m_height, int bits);
	BOOL InitGL();
	BOOL InitProgramInfo();
	BOOL InitLightsInfo();
	BOOL InitObjects();

	void toggleFullScreen();

	static bool keys[255];
	static bool IsKeyPressed(unsigned short key);
	static bool IsButtonPressed(unsigned int);
	bool isQuitGame();

	virtual void RenderScene();
	void RenderMesh(Mesh *mesh, bool enableLight, bool enableFog);
	void Render2DMesh(Mesh *mesh, bool enableLight, bool enableFog, float sizeX, float sizeY, float transX, float transY); //on screen
	void RenderGameTextOnScreen(Mesh * mesh, std::string text, Color color, float size, float x, float y);
	void RenderTile(Mesh* mesh, int TileID);
	void RenderTileOnScreen(Mesh * mesh, bool enableLight, int TileID, float size, float x, float y);
	void RenderLevel(int levelID);
	void RenderTileMap(CMap * mapToRender);

	void Update(double dt);
	void UpdateSA(double dt);

	void Exit();

	ViewHandler* getInstance(){ return this; }

	void setViewType(VIEW_TYPE type)
	{
		this->view_type = type;
	}
	VIEW_TYPE getViewType()
	{
		return this->view_type;
	}

	MS projectionStack;
	MS viewStack;
	MS modelStack;

	Mouse MouseInfo;
private:
	GLFWwindow* m_window;
	ModelHandler * theModel;

	std::vector<unsigned char> m_heightMap;

	int tileOffset_x, tileOffset_y;

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* m_meshList[NUM_GEOMETRY];

	Light lights[1];
	bool LightsEnabled;

	const static int m_window_deadzone = 100;
	const static int m_window_width = 1024;
	const static int m_window_height = 800;

	int m_width;
	int m_height;
	
	bool m_bFullScreen;

	float FPS;
	double TimeToExit;

	GLint m_viewPort[4];
	VIEW_TYPE view_type;
};

#endif
