#include "TextBox.h"
#include <iostream>

CTextBox::CTextBox()
{
	typewriterIndex = 0;
	sentenceIndex = 0;
	paragraphIndex = 0;
	episodeIndex = 0;
	inText = false;

	finishTypewriter = false;
	initTextBox = false;
	speedUpText = false;

	typewriterDelay = 0.f;
}

CTextBox::~CTextBox()
{
}

bool CTextBox::isFinished()
{
	return finishTypewriter;
}

bool CTextBox::paragraphFinished()
{

	if (sentenceIndex == TextDatabase.getSentences(episodeIndex, paragraphIndex)-1)
	{
		return true;
	}

	return false;
}

string CTextBox::getText()
{
	return text;
}

std::array<string, 5> CTextBox::getTextToRender()
{
	std::array<string, 5> temp;

	temp[0] = textbox1;
	temp[1] = textbox2;
	temp[2] = textbox3;
	temp[3] = textbox4;
	temp[4] = textbox5;

	return temp;
}

void CTextBox::nextSentence()
{
	this->sentenceIndex += 1;

	TextToRender(episodeIndex, paragraphIndex, sentenceIndex);
}

void CTextBox::nextEpisode()
{
	this->episodeIndex += 1;
}

bool CTextBox::getSpeed()
{
	return speedUpText;
}

void CTextBox::SpeedUp(bool speed)
{
	this->speedUpText = speed;

	if (speed)
	{
		textbox1 = text1buffer;
		textbox2 = text2buffer;
		textbox3 = text3buffer;
		textbox4 = text4buffer;
		textbox5 = text5buffer;
		this->speedUpText = false;
	}
}

void CTextBox::setParagraph(int paragraphNum)
{
	this->sentenceIndex = 0;

	textbox1 = ""; textbox2 = ""; textbox3 = ""; textbox4 = ""; textbox5 = "";
	text1buffer = ""; text2buffer = ""; text3buffer = ""; text4buffer = ""; text5buffer = "";
	finishTypewriter = false;

	paragraphIndex = paragraphNum;

	initText();


}

void CTextBox::UpdateText(double dt)
{
	typewriterDelay += static_cast<float>(dt);
	finishTypewriter = false;

	if (this->getSpeed())
	{
		this->SpeedUp(true);
	}

	if (text1buffer != "" && textbox1 != text1buffer && typewriterIndex != text1buffer.length()+1 && typewriterDelay > 0.03f)
	{
		textbox1.assign(text1buffer, 0, typewriterIndex);

		typewriterDelay = 0.f;
		typewriterIndex += 1;

		if (typewriterIndex == text1buffer.length()+1)
			typewriterIndex = 0;
	}
	else if (text2buffer != "" && textbox2 != text2buffer && typewriterIndex != text2buffer.length()+1 && typewriterDelay > 0.03f)
	{
		textbox2.assign(text2buffer, 0, typewriterIndex);

		typewriterDelay = 0.f;
		typewriterIndex += 1;

		if (typewriterIndex == text2buffer.length()+1)
			typewriterIndex = 0;
	}
	else if (text3buffer != "" && textbox3 != text3buffer && typewriterIndex != text3buffer.length()+1 && typewriterDelay > 0.03f)
	{
		textbox3.assign(text3buffer, 0, typewriterIndex);

		typewriterDelay = 0.f;
		typewriterIndex += 1;

		if (typewriterIndex == text3buffer.length()+1)
			typewriterIndex = 0;
	}
	else if (text4buffer != "" && textbox4 != text4buffer && typewriterIndex != text4buffer.length()+1 && typewriterDelay > 0.03f)
	{
		textbox4.assign(text4buffer, 0, typewriterIndex);

		typewriterDelay = 0.f;
		typewriterIndex += 1;

		if (typewriterIndex == text4buffer.length()+1)
			typewriterIndex = 0;
	}
	else if (text5buffer != "" && textbox5 != text2buffer && typewriterIndex != text5buffer.length()+1 && typewriterDelay > 0.03f)
	{
		textbox5.assign(text5buffer, 0, typewriterIndex);

		typewriterDelay = 0.f;
		typewriterIndex += 1;
	}
	else if (textbox1 == text1buffer && textbox2 == text2buffer && textbox3 == text3buffer && textbox4 == text4buffer && textbox5 == text5buffer && textbox1 != "")
	{
		finishTypewriter = true;
	}
}

void CTextBox::TextToRender(int episodeNum, int paragraphNum, int sentenceNum)
{
	if (textbox1 != "")
	{
		finishTypewriter = false;
		initTextBox = false;
		speedUpText = false;

		typewriterIndex = 0;
	}

	textbox1 = ""; textbox2 = ""; textbox3 = ""; textbox4 = ""; textbox5 = "";
	text1buffer = ""; text2buffer = ""; text3buffer = ""; text4buffer = ""; text5buffer = "";

	std::string text = TextDatabase.getText(episodeNum, paragraphNum, sentenceIndex);	
	this->text = text;

	if(text.length() > 25)
	{
		std::string temp = text;
		for (int i = 25; i > 0; i--) // If string longer than 25
		{
			if (temp[i] == ' ')
			{
				text1buffer = temp; // Assign first <25 characters
				text1buffer.resize(i); 

				temp.erase(0, i+1); // Remove assigned characters (including whitespace) from string

				if (temp.length() > 25) // If string still longer than 25
				{
					for (int i = 25; i > 0; i--)
					{
						if (temp[i] == ' ')
						{
							text2buffer = temp; // Assign second line of  <25 characters
							text2buffer.resize(i); 

							temp.erase(0, i+1); // Remove assigned characters (including whitespace) from string

							if (temp.length() > 25) // If string still longer than 25
							{
								for (int i = 25; i > 0; i--)
								{
									if (temp[i] == ' ')
									{
										text3buffer = temp; // Assign third line of  <25 characters
										text3buffer.resize(i); 

										temp.erase(0, i+1); // Remove assigned characters (including whitespace) from string

										if (temp.length() > 25) // If string still longer than 25
										{
											for (int i = 25; i > 0; i--)
											{
												if (temp[i] == ' ')
												{
													text4buffer = temp; // Assign fourth line of  <25 characters
													text4buffer.resize(i); 

													temp.erase(0, i+1); // Remove assigned characters (including whitespace) from string

													if (temp.length() > 25) // If string still longer than 25
													{
														break;
													}
													else
													{
														text5buffer = temp;
													}

													break;
												}
											}
										}
										else
										{
											text4buffer = temp;
										}

										break;
									}
								}
							}
							else
							{
								text3buffer = temp;
							}

							break;
						}
					}
				}
				else
				{
					text2buffer = temp;
				}

				break;
			}
		}
	}
	else
	{
		text1buffer = text;
	}
}
 
void CTextBox::initText()
{
	if (textbox1 == "")
 		TextToRender(episodeIndex, paragraphIndex, sentenceIndex);
}

void CTextBox::resetSentenceIndex()
{
	this->sentenceIndex = 0;
}