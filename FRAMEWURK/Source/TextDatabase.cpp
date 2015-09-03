#include "TextDatabase.h"

#define NUM_EPISODES 10

#define NUM0_PARAGRAPHS 1
#define NUM1_PARAGRAPHS	8

CTextDatabase::CTextDatabase()
{
	m_Text[0][0].push_back( static_cast<string>("Welcome to Phobia Run!"));
	m_Text[0][0].push_back( static_cast<string>("Move Around with the WASD Keys"));
	m_Text[0][0].push_back( static_cast<string>("You can press E to interact with things"));
	m_Text[0][0].push_back( static_cast<string>("Try it! Walk to the top of one the beds and Press E"));

	m_Text[1][0].push_back( static_cast<string>("Where....am I?"));
	m_Text[1][0].push_back( static_cast<string>("Ughhhhhh..my head hurts.."));

	m_Text[1][1].push_back( static_cast<string>("*You opened the drawer*"));
	m_Text[1][1].push_back( static_cast<string>("Theres a key here! I should probably take it."));
	m_Text[1][1].push_back( static_cast<string>("*You obtained Mysterious Key*"));

	m_Text[1][2].push_back( static_cast<string>("...?"));

	m_Text[1][3].push_back( static_cast<string>("The hallway looks creepy.."));

	m_Text[1][4].push_back( static_cast<string>("The door is locked"));
	m_Text[1][4].push_back( static_cast<string>("I should look for a key."));

	m_Text[1][5].push_back( static_cast<string>("*You put the key through the keyhole*"));
	m_Text[1][5].push_back( static_cast<string>("*Click!* The door slides open"));

	m_Text[1][6].push_back( static_cast<string>("I can press [A] to attack"));
	m_Text[1][6].push_back( static_cast<string>("Death to bushes!!!"));

	m_Text[1][7].push_back( static_cast<string>("OBTAINED LEGENDARY SWORD!"));
	m_Text[1][7].push_back( static_cast<string>("It's just a fruit knife..."));
	m_Text[1][7].push_back( static_cast<string>("At least it's useful!"));

	m_Text[1][8].push_back( static_cast<string>("How did this piece of paper end up on my knife?"));
	m_Text[1][8].push_back( static_cast<string>("I've never heard of this hero academy. And it sounds fake."));
	m_Text[1][8].push_back( static_cast<string>("But if this is real..."));
	m_Text[1][8].push_back( static_cast<string>("... I have nothing better to do anyway. I should try finding the next piece of paper."));

	m_Text[1][9].push_back( static_cast<string>("I should press [P] to read the paper"));

	m_Text[1][10].push_back( static_cast<string>("MUSHROOMS!"));

	m_Text[1][11].push_back(  static_cast<string>("There's a piece of paper here."));
	m_Text[1][11].push_back(  static_cast<string>("I should press [P] to read the paper"));

	m_Text[1][12].push_back(  static_cast<string>("I think I saw something brown in the tree I just passed."));
	m_Text[1][12].push_back(  static_cast<string>("I should check it out"));

	m_Text[1][13].push_back(  static_cast<string>("..........."));
	m_Text[1][13].push_back(  static_cast<string>("???? ?? ????????? ?? ?? ???"));

	m_Text[1][14].push_back(  static_cast<string>("Oh my!"));
	m_Text[1][14].push_back(  static_cast<string>("I've been freed from the curse! >//<"));
	m_Text[1][14].push_back(  static_cast<string>("If you're intending on entering the CAVE to remove the curse, you'll need to teleport!"));
	m_Text[1][14].push_back(  static_cast<string>("The doll by the dragon statue will allow you to teleport. Head southwest!"));
	m_Text[1][14].push_back(  static_cast<string>("Good luck!"));

	m_Text[1][15].push_back(  static_cast<string>("The doll disappears when I tried to pick it up."));
	m_Text[1][15].push_back(  static_cast<string>("My body feels lighter and I can move more easily"));
	m_Text[1][15].push_back(  static_cast<string>("Press CTRL to teleport!"));

	m_Text[1][16].push_back(  static_cast<string>("The portal malfunctions and you die. The world will be destroyed. The End."));

	m_Text[1][17].push_back(  static_cast<string>("You have dead."));

	m_Text[1][18].push_back(  static_cast<string>(""));
}


CTextDatabase::~CTextDatabase()
{
}

string CTextDatabase::getText(int episodeNum, int paragraphNum, int sentenceNum)
{
	string temp = "";

	if (episodeNum < NUM_EPISODES)
	{
		temp = m_Text[episodeNum][paragraphNum][sentenceNum];
	}

	return temp;
}

int CTextDatabase::getSentences(int episodeNum, int paragraphNum)
{
	if (episodeNum < NUM_EPISODES)
	{
		return m_Text[episodeNum][paragraphNum].size();
	}

	return -1;
}