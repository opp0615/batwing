#pragma once
#include "cocos2d.h"

using namespace cocos2d;



class Score
{
private:
	int s_digit0;
	int s_digit1;
	int s_digit2;
	int s_digit3;
	int s_digit4;
	int s_digit5;
	int s_digit6;
	int s_digit7;
	int s_digit8;

	int s_score;
public:
	Score();

	int getScore();
	void setScore(int score);
	
	int getFistDigit();
	void setFirstDigit(int first_digit);

	int getSecondDigit();
	void setSecondDigit(int second_digit);

	int getThirdDigit();
	void setThirdDigit(int third_digit);

	int getForthDigit();
	void setForthDigit(int forth_digit);

	int getFifthDigit();
	void setFifthDigit(int fifth_digit);

	int getSixthDigit();
	void setSixthDigit(int six_digit);
};