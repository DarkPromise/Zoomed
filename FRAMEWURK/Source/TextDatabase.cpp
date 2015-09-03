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

	m_Text[1][6].push_back( static_cast<string>("Theres a switch behind the poster!"));
	m_Text[1][6].push_back( static_cast<string>("You flipped the switch"));
	m_Text[1][6].push_back( static_cast<string>("*Chic...zz.....CLUNK!*"));
	m_Text[1][6].push_back( static_cast<string>("There was a huge fizz sound"));
	m_Text[1][6].push_back( static_cast<string>("and a clunk in the distance."));
	m_Text[1][6].push_back( static_cast<string>("Sounds like something has dropped in the room nearby"));

	m_Text[1][7].push_back( static_cast<string>("The switch has already been flipped"));

	m_Text[1][8].push_back( static_cast<string>("Wha-..what is that thing!?"));

	m_Text[1][9].push_back( static_cast<string>("Theres a key on the floor..."));
	m_Text[1][9].push_back( static_cast<string>("You walked over to the key"));
	m_Text[1][9].push_back( static_cast<string>("*You obtained Desk Key*"));

	m_Text[1][10].push_back( static_cast<string>("The desk is locked"));

	m_Text[1][11].push_back(  static_cast<string>("There's a piece of paper here."));
	m_Text[1][11].push_back(  static_cast<string>("It looks like a charm.."));
	m_Text[1][11].push_back(  static_cast<string>("You obtained Exorcising Charm!"));

	m_Text[1][12].push_back(  static_cast<string>("Theres nothing left inside"));

	m_Text[1][13].push_back(  static_cast<string>("There are some spiritual salt in the cupboard"));
	m_Text[1][13].push_back(  static_cast<string>("You took the salt."));

	m_Text[1][14].push_back(  static_cast<string>("The door seems sealed"));

	m_Text[1][15].push_back(  static_cast<string>("...? It seems you have woken up."));

	m_Text[1][16].push_back(  static_cast<string>("Theres a charm missing"));

	m_Text[1][17].push_back(  static_cast<string>("Theres an incomplete salt circle.. wait what?"));

	m_Text[1][18].push_back(  static_cast<string>(""));

	m_Text[2][0].push_back( static_cast<string>("This.."));
	m_Text[2][0].push_back( static_cast<string>("It's the class I was studying in"));
	m_Text[2][0].push_back( static_cast<string>("It's where we were..."));

	m_Text[2][1].push_back( static_cast<string>("It's a newspaper article about us..."));
	m_Text[2][1].push_back( static_cast<string>("I should collect these."));

	m_Text[2][2].push_back( static_cast<string>("It's a newspaper article about us..."));
	m_Text[2][2].push_back( static_cast<string>("I should collect these."));
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