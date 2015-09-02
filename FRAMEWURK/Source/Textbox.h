#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "TextDatabase.h"
#include <string>
#include <vector>
#include <array>

using std::string;
using std::vector;

class CTextBox
{
public:
	CTextBox();
	~CTextBox();

	bool isFinished(); // Returns if text has been rendered
	bool paragraphFinished(); // Returns if all sentences has been rendered
	string getText(); // returns whole text string
	std::array<string, 5> getTextToRender(); // returns text to render
	void nextSentence(); // sentenceIndex++ (goes to next sentence)
	void nextEpisode(); // Goes to next episode (affects text database)
	void setParagraph(int paragraphNum); // Sets what paragraph to render
	bool getSpeed(); // Returns speed value
	void SpeedUp(bool speed); // Renders all text at once
	void TextToRender(int episodeNum, int paragraphNum, int sentenceNum); // passes in text to render (from database)
	void UpdateText(double dt); // update text to render
	void initText(); // Prepare text to render
	void resetSentenceIndex(); // set sentence index to 0
	//virtual void
	//virtual void UpdateTextBox(double dt);
	//virtual void RenderParagraph(float posX, float posY);
	//virtual void RenderTextBox(int width, int height, string text, float posX, float posY);
	//virtual void RenderText(int paragraphNum);
	
	string text;
	string textbox1, textbox2, textbox3, textbox4, textbox5;
	string text1buffer, text2buffer, text3buffer, text4buffer, text5buffer;

	bool inText;
private:
	int typewriterIndex;

	int sentenceIndex;
	int paragraphIndex;
	int episodeIndex;

	bool finishTypewriter;
	bool initTextBox;
	bool speedUpText;

	float typewriterDelay;

	CTextDatabase TextDatabase;
};

#endif
