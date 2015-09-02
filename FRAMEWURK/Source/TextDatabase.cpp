#include "TextDatabase.h"

#define NUM_EPISODES 10

#define NUM0_PARAGRAPHS 1
#define NUM1_PARAGRAPHS	8

CTextDatabase::CTextDatabase()
{
	m_Text[0][0].push_back( static_cast<string>("I AM THE MAIN CHARACTER OF THIS NON EXISTANT STORY!"));
	m_Text[0][0].push_back( static_cast<string>("Lets pretend I cursed the world and now there're monsters"));
	m_Text[0][0].push_back( static_cast<string>("Now I need to be the hero."));

	m_Text[1][0].push_back( static_cast<string>("I need to undo the curse or I can't get back into the village"));
	m_Text[1][0].push_back( static_cast<string>("I should find my knife."));

	m_Text[1][1].push_back( static_cast<string>("I can't go back until I undo the curse"));
	m_Text[1][1].push_back( static_cast<string>("I should start by checking the elder tree on the right."));

	m_Text[1][2].push_back( static_cast<string>("...?"));

	m_Text[1][3].push_back( static_cast<string>("Whoa... The village really is gone"));
	m_Text[1][3].push_back( static_cast<string>("Damn. I guess hero academy really does exist"));
	m_Text[1][3].push_back( static_cast<string>("Sounds a bit lame though..."));

	m_Text[1][4].push_back( static_cast<string>("Typical bushes that block your path."));
	m_Text[1][4].push_back( static_cast<string>("I would just step over it but it's prickly."));
	m_Text[1][4].push_back( static_cast<string>("I should get my knife to cut through these bushes."));

	m_Text[1][5].push_back( static_cast<string>("I hid my knife somewhere around here"));
	m_Text[1][5].push_back( static_cast<string>("I should go pick it up."));

	m_Text[1][6].push_back( static_cast<string>("I can press [A] to attack"));
	m_Text[1][6].push_back( static_cast<string>("Death to bushes!!!"));

	m_Text[1][7].push_back( static_cast<string>("OBTAINED LEGENDARY SWORD!"));
	m_Text[1][7].push_back( static_cast<string>("It's just a fruit knife..."));
	m_Text[1][7].push_back( static_cast<string>("At least it's useful!"));
	//m_Text[1][7].push_back( static_cast<string>("Wait..."));
	//m_Text[1][7].push_back( static_cast<string>("There's a piece of paper attached to my knife?"));
	//m_Text[1][7].push_back( static_cast<string>("I can press [P] to look at the paper."));

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