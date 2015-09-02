#ifndef TEXT_DATABASE_H
#define TEXT_DATABASE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class CTextDatabase
{
public:
	CTextDatabase();
	~CTextDatabase();
	
	string getText(int episodeNum, int paragraphNum, int sentenceNum);
	int getSentences(int episodeNum, int paragraphNum);
private:
	vector<string> m_Text[2][50];


};
#endif
