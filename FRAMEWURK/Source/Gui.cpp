#include "Gui.h"


Gui::Gui(std::string guiName, const char * imagePath) : m_GUIPos(Vector3(0.f,0.f,0.f))
{
	this->m_UIName = guiName;

	this->m_GUIMesh = MeshBuilder::GenerateQuad(guiName,Color(0.f,0.f,0.f),1.f);
	
	//GUI is rendered on screen, hence textureID
	this->m_GUIMesh->textureID = LoadTGA(imagePath);
}

Gui::~Gui(void)
{
	delete m_GUIMesh;
	m_GUIMesh = NULL;
}

Mesh * Gui::getMesh()
{
	return this->m_GUIMesh;
}

void Gui::setPosition(Vector3 position)
{
	this->m_GUIPos.x = position.x;
	this->m_GUIPos.y = position.y;
	this->m_GUIPos.z = position.z;
}

Vector3 Gui::getPosition()
{
	return this->m_GUIPos;
}
