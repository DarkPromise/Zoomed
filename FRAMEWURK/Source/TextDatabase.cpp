#include "TextDatabase.h"

#define NUM_EPISODES 10

#define NUM0_PARAGRAPHS 1
#define NUM1_PARAGRAPHS	8

CTextDatabase::CTextDatabase()
{
	m_Text[0][0].push_back( static_cast<string>("I AM THE MAIN CHARACTER OF THIS NON EXISTANT STORY!"));
	m_Text[0][0].push_back( static_cast<string>("Lets pretend I cursed the world and now there're monsters"));
	m_Text[0][0].push_back( static_cast<string>("Now I need to be the hero."));

	m_Text[0][1].push_back( static_cast<string>("The robots never sleep, only replicate"));
	m_Text[0][1].push_back( static_cast<string>("There is no fight. Hide, and run!"));
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