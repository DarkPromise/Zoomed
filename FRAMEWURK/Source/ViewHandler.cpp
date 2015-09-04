#include "ViewHandler.h"

bool ViewHandler::keys[255];

ViewHandler::ViewHandler(ModelHandler * theModel)
{
	this->theModel = theModel;

	this->view_type = VIEW_SIDESCROLLER;

	for(int i = 0; i < 255; i++)
	{
		keys[i] = false;
	}

	m_bFullScreen = false;
	TimeToExit = 0.0;
	tileOffset_x = 0;
	tileOffset_y = 0;

	std::cout << "View Handler Initialized" << std::endl;
}

ViewHandler::~ViewHandler(void)
{ 
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//ViewHandler::IsKeyPressed(key);
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(button >= 0 && button < 8)
	{
		if(action == GLFW_PRESS)
		{
			ViewHandler::keys[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			ViewHandler::keys[button] = false;
		}
	}
}

static void resize_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0,0,width,height);
}

bool ViewHandler::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool ViewHandler::IsButtonPressed(unsigned int button)
{
	return ViewHandler::keys[button];
}

BOOL ViewHandler::InitGL() //Initialize OpenGL Values
{ 
	glShadeModel(GL_SMOOTH);
	glClearColor(0.f,0.f,0.f,0.5f); //Initialize Background Colour
	glEnable(GL_DEPTH_TEST); //Enable Depth Test
	glDepthFunc(GL_LEQUAL); //If the image is closer to camera, allow it to be ontop
	glEnable(GL_CULL_FACE); //Allow culling of faces
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //Allows the interior of polygon to be filled
	glEnable(GL_BLEND); //Allow blending of textures with alpha
	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB); //Perfect Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); //Alpha stuff
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); //Nicest Perspective that can be calculated

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//glfwSetInputMode(m_window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	if(!InitProgramInfo())
	{
		std::cout << "Failed to Load Program Viewing Parameters" << std::endl;
	}
	if(!InitLightsInfo())
	{
		std::cout << "Failed to Load Lights" << std::endl;
	}
	if(!InitObjects())
	{
		std::cout << "Failed to Create Objects" << std::endl;
	}
	return TRUE;
}

BOOL ViewHandler::InitProgramInfo()
{
	m_programID = LoadShaders( "Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader" );
	//Model View
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	//Material
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	//Lights
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	//Color
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");
	//Text
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	//Fog *Not yet added
	m_parameters[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fog[0].color.r");
	m_parameters[U_FOG_START] = glGetUniformLocation(m_programID, "fog[0].start");
	m_parameters[U_FOG_END] = glGetUniformLocation(m_programID, "fog[0].end");
	m_parameters[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fog[0].density");
	m_parameters[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fog[0].type");
	m_parameters[U_FOG_ENABLE] = glGetUniformLocation(m_programID, "fogEnabled");

	glUseProgram(m_programID); //Use our own shader
	return true;
}

BOOL ViewHandler::InitLightsInfo()
{
	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(-20, 30, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	return true;
}

BOOL ViewHandler::InitObjects() //Object textures, etc...
{
	LightsEnabled = false;
	return true;
}

BOOL ViewHandler::CreateGLWindow(char * title, int m_width, int m_height, int bits)
{
	glfwSetErrorCallback(error_callback);

	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	if(m_bFullScreen)
	{
		m_window = glfwCreateWindow(m_width, m_height, title , glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		m_window = glfwCreateWindow(m_width, m_height, title , NULL, NULL);
	}

	if(!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	//Sets the callbacks
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glGetIntegerv(GL_VIEWPORT,m_viewPort);
	glViewport(0,0,m_window_width,m_window_height); //MAKING IT LOOK NICE, height should be same as width to prevent squeezing

	glewExperimental = true;

	GLenum err = glewInit();

	if(err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if(!InitGL())
	{
		return FALSE;
	}

	std::cout << "OPENGL WINDOW CREATED" << std::endl;

	return TRUE;
}

void ViewHandler::toggleFullScreen()
{
	if(!m_bFullScreen)
	{
		m_bFullScreen = true;
		glfwDestroyWindow(m_window);
		std::cout << "Destroyed Window" << std::endl;
		CreateGLWindow("Full Screen",m_window_width,m_window_height,16);
	}
	else
	{
		m_bFullScreen = false;
		glfwDestroyWindow(m_window);
		std::cout << "Destroyed Window" << std::endl;
		CreateGLWindow("Windowed Size",m_window_width,m_window_height,16);
	}
}

void ViewHandler::UpdateSA(double dt)
{
	SpriteAnimation *sprite = dynamic_cast<SpriteAnimation*>(theModel->m_objectList[OBJ_PLAYER]->getMesh());
	if (sprite)
	{
		sprite->Update(dt);
	}

	sprite = dynamic_cast<SpriteAnimation*>(theModel->m_objectList[OBJ_ENEMYSISTER]->getMesh());
	if (sprite)
	{
		sprite->Update(dt);
	}

	sprite = dynamic_cast<SpriteAnimation*>(theModel->m_objectList[OBJ_ENEMYFATHER]->getMesh());
	if (sprite)
	{
		sprite->Update(dt);
	}

	sprite = dynamic_cast<SpriteAnimation*>(theModel->m_objectList[OBJ_DASHER]->getMesh());
	if (sprite)
	{
		sprite->Update(dt);
	}

	sprite = dynamic_cast<SpriteAnimation*>(theModel->m_objectList[OBJ_GHOST]->getMesh());
	if (sprite)
	{
		sprite->Update(dt);
	}
}

void ViewHandler::Update(double dt)
{
	glfwGetCursorPos(m_window, &MouseInfo.x, &MouseInfo.y); //Update Cursor Coordinates
	glGetIntegerv(GL_VIEWPORT,m_viewPort);
	UpdateSA(dt);

	if(ViewHandler::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(ViewHandler::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(ViewHandler::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(ViewHandler::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	this->theModel->Update(dt);
	FPS = 1 / (float)dt;
}

void ViewHandler::RenderMesh(Mesh *mesh, bool enableLight, bool enableFog)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if(enableLight && LightsEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	for(int i = 0; i < MAX_TEXTURES; i++)
	{
		if(mesh->textureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
		//
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//
		glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
	}

	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void ViewHandler::Render2DMesh(Mesh *mesh, bool enableLight, bool enableFog, float sizeX, float sizeY, float transX, float transY)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, m_width, 0, m_height, -10, 1000);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(transX, transY, 0);
	modelStack.Scale(sizeX, sizeY, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

void ViewHandler::RenderTile(Mesh* mesh, int TileID)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_RECTANGLE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_RECTANGLE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	Mtx44 characterSpacing;
	characterSpacing.SetToTranslation(0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	mesh->Render((unsigned)TileID * 6, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

void ViewHandler::RenderTileOnScreen(Mesh*mesh, bool enableLight, int TileID, float size, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, m_width, 0, m_height, -10, 100000);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_TEXTURE_RECTANGLE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_RECTANGLE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	Mtx44 characterSpacing;
	characterSpacing.SetToTranslation(0.5f, 6.5f, 0); //1.0f is the spacing of each character, you may change this value
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top()  * characterSpacing;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	mesh->Render((unsigned)TileID * 6, 6);

	glBindTexture(GL_TEXTURE_2D, 0);

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void ViewHandler::RenderGameTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, m_width, 0, m_height, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.45f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void ViewHandler::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.LoadIdentity(); //Setting point of origin at 0,0,0

	//Enable Light Position
	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 LightDirection(lights[0].position.x,lights[0].position.y,lights[0].position.z);
		Vector3 LightDirection_cameraspace = viewStack.Top() * LightDirection;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION],1,&LightDirection_cameraspace.x);
	}

	glfwGetWindowSize(m_window,&m_width,&m_height);
	glViewport(0,0,m_width,m_height);

	Mtx44 Projection;
	Projection.SetToOrtho(0, m_width, 0, m_height, -10, 1000);
	projectionStack.LoadIdentity();
	projectionStack.LoadMatrix(Projection);

	if (theModel->currentWorld == WORLD_FRIENDS_TUTORIAL)
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(
			(theModel->getFriend()->GetPos_x() + theModel->getPlayer()->getPosition().x)/2 - Math::Round((m_width * 0.5f)), (theModel->getFriend()->GetPos_y() + theModel->getPlayer()->getPosition().y)/2 - Math::Round((m_height * 0.5f)), theModel->getCamera().position.z,
			(theModel->getFriend()->GetPos_x() + theModel->getPlayer()->getPosition().x)/2 - Math::Round((m_width * 0.5f)), (theModel->getFriend()->GetPos_y() + theModel->getPlayer()->getPosition().y)/2 - Math::Round((m_height * 0.5f)), theModel->getCamera().target.z,
			theModel->getCamera().up.x,theModel->getCamera().up.y,theModel->getCamera().up.z
			);
	}
	else
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(
			theModel->getPlayer()->getPosition().x - Math::Round((m_width * 0.5f)),theModel->getPlayer()->getPosition().y - Math::Round((m_height * 0.5f)),theModel->getCamera().position.z,
			theModel->getPlayer()->getPosition().x - Math::Round((m_width * 0.5f)),theModel->getPlayer()->getPosition().y - Math::Round((m_height * 0.5f)),theModel->getCamera().target.z,
			theModel->getCamera().up.x,theModel->getCamera().up.y,theModel->getCamera().up.z
			);
	}

	for(unsigned i = 0; i < theModel->m_objectList.size(); ++i)
	{
		if(theModel->m_objectList[i]->getMeshSize() > 1)
		{
			if (theModel->m_objectList[i]->isAlive || theModel->m_objectList[i]->isVisible)
			{
				if(theModel->m_objectList[i]->getObjectType() == TYPE_MAP)
				{
					if (theModel->currentWorld+2 == i)
					{
						modelStack.PushMatrix();
						modelStack.Translate(theModel->m_objectList[i]->getPosition().x, theModel->m_objectList[i]->getPosition().y, theModel->m_objectList[i]->getPosition().z);
						RenderMesh(theModel->m_objectList[i]->getMesh(0),false,false); //Background
						RenderMesh(theModel->m_objectList[i]->getMesh(1),false,false); //Scenery

						for (unsigned j = 0; j < theModel->m_objectList.size(); ++j)
						{
							if(theModel->m_objectList[j]->getObjectType() == TYPE_ENEMY && theModel->m_objectList[j]->isAlive)
							{
								modelStack.PushMatrix();
								modelStack.Translate(theModel->m_objectList[j]->getPosition().x,theModel->m_objectList[j]->getPosition().y,theModel->m_objectList[j]->getPosition().z);
								RenderMesh(theModel->m_objectList[j]->getMesh(),false,false);
								modelStack.PopMatrix();
							}
						}
						if(!theModel->getPlayer()->getIsHiding())
						{
							modelStack.PushMatrix();
							modelStack.Translate(theModel->getPlayer()->getPosition().x,theModel->getPlayer()->getPosition().y, theModel->getPlayer()->getPosition().z);
							RenderMesh(theModel->m_objectList[0]->getMesh(0), false, false);
							modelStack.PopMatrix();
						}
						RenderMesh(theModel->m_objectList[i]->getMesh(2),false,false); //Foreground
						modelStack.PopMatrix();
					}
				}
				else
				{
					for(int j = 0; j < theModel->m_objectList[i]->getMeshSize(); ++j)
					{
						RenderMesh(theModel->m_objectList[i]->getMesh(j),false,false);
					}
				}
			}
		}
		else
		{
			if(theModel->m_objectList[i]->isAlive)
			{
				if(theModel->m_objectList[i]->isVisible)
				{
					if(theModel->m_objectList[i]->getObjectType() != TYPE_TEXT && theModel->m_objectList[i]->getObjectType() != TYPE_TEXTBOX && theModel->m_objectList[i]->getObjectType() != TYPE_AXES && theModel->m_objectList[i]->getObjectType() != TYPE_PLAYER)
					{
						RenderMesh(theModel->m_objectList[i]->getMesh(),false,false);
					}
				}
			}
		}
	}

	if (theModel->getTextBox()->inText)
	{
		theModel->getTextBox()->initText();

		if (theModel->getTextBox()->isFinished())
		{
			Render2DMesh(theModel->m_objectList[OBJ_TEXTBOX2]->getMesh(),false,false, 360.f, 120.f, m_viewPort[2] *0.5f,  (m_viewPort[3] * 0.5f) - 100);
		}
		else
		{ 
			Render2DMesh(theModel->m_objectList[OBJ_TEXTBOX2]->getMesh(),false,false, 360.f, 120.f, m_viewPort[2] *0.5f,  (m_viewPort[3] * 0.5f) - 100);
		}

		RenderGameTextOnScreen(theModel->m_objectList[OBJ_FONTBASIS33]->getMesh(), theModel->getTextBox()->getTextToRender()[0], Color(1,1,1), 28.f, (m_viewPort[2] *0.5f - 170),  (m_viewPort[3] * 0.5f) - 75);
		RenderGameTextOnScreen(theModel->m_objectList[OBJ_FONTBASIS33]->getMesh(), theModel->getTextBox()->getTextToRender()[1], Color(1,1,1), 28.f, (m_viewPort[2] *0.5f - 170),  (m_viewPort[3] * 0.5f) - 100);
	}

	/*for(int i = 0; i < theModel->m_objectList.size(); ++i)
	{
	std::cout << "ID : " << i << " " << theModel->m_objectList[i]->ToString() << std::endl;
	}*/

	if(theModel->getPlayer()->isDead)
	{
		Render2DMesh(theModel->m_guiList[4]->getMesh(),false,false,512.f,128.f, m_viewPort[2] * 0.5f,  m_viewPort[3] * 0.5f);

		if(this->IsKeyPressed(VK_RETURN))
		{
			theModel->getPlayer()->isDead = false;
			theModel->getPlayer()->setIsHiding(false);
			theModel->currentWorld = WORLD_MAINMENU;
			theModel->getCurrLevel() = 0;
			theModel->getPlayer()->setPosition(Vector3(800, -1248, 0));
			theModel->getPlayer()->getCurrFear() = 0.f;
		}
	}
	else
	{
		std::ostringstream s1;
		s1.precision(3);
		s1 << "LEVEL "<< theModel->getCurrLevel();

		RenderGameTextOnScreen(theModel->m_objectList[OBJ_FONTONRYOU]->getMesh(),"FEAR", Color(1,0,0), 28.f, GameUIFearWidthOffset,m_viewPort[3] - GameUIFearHeightOffset);
		RenderGameTextOnScreen(theModel->m_objectList[OBJ_FONTONRYOU]->getMesh(),s1.str(), Color(1,0,0), 48.f,  (m_viewPort[2] - GameUILevelWidthOffset), m_viewPort[3] - GameUIHeightOffset);

		Render2DMesh(theModel->m_guiList[3]->getMesh(),false,false,208.f * theModel->getPlayer()->getSanity() ,55.f * theModel->getPlayer()->getSanity(),(m_viewPort[2] * 0.5f), (m_viewPort[3] - (m_viewPort[3]) + GameUISanityHeightOffset));

		Render2DMesh(theModel->getPlayer()->getInventory().getItem(1)->getMesh(),false,false,32.f,32.f,GameUIWidthOffset,(m_viewPort[3] - (m_viewPort[3]) + GameUIHeightOffset));
		Render2DMesh(theModel->getPlayer()->getInventory().getItem(1)->getMesh(),false,false,32.f,32.f,(GameUIWidthOffset * 2.f) + (GameUIWidthOffset * 0.5f),(m_viewPort[3] - (m_viewPort[3]) + GameUIHeightOffset));

		Render2DMesh(theModel->m_guiList[0]->getMesh(),false,false,50.f,50.f,GameUIWidthOffset,(m_viewPort[3] - (m_viewPort[3]) + GameUIHeightOffset)); // Consumable
		Render2DMesh(theModel->m_guiList[0]->getMesh(),false,false,50.f,50.f,(GameUIWidthOffset * 2.f) + (GameUIWidthOffset * 0.5f),(m_viewPort[3] - (m_viewPort[3]) + GameUIHeightOffset)); // Equipment

		Render2DMesh(theModel->m_guiList[2]->getMesh(),false,false,40.f,300.f * (theModel->getPlayer()->getCurrFear() * 0.01f),GameUIFearBorderWidthOffset, m_viewPort[3] - (GameUIFearValueHeightOffset + (30.f - theModel->getPlayer()->getCurrFear() * 1.5f)));
		Render2DMesh(theModel->m_guiList[1]->getMesh(),false,false,40.f,300.f,GameUIFearBorderWidthOffset, m_viewPort[3] - GameUIFearBorderHeightOffset);
	}

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool ViewHandler::isQuitGame()
{
	if(ViewHandler::IsKeyPressed(VK_ESCAPE) || glfwWindowShouldClose(m_window))
	{
		//Prompt confirmation
		return true;
	}
	return false;
}