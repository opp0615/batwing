#include "Score.h"


Score::Score()
{

	s_digit1=0;
	s_digit2=0;
	s_digit3=0;
	s_digit4=0;
	s_digit5=0;

	s_score=0;
};

int Score::getScore()
{
	return s_score;
}
void Score::setScore(int score)
{
	s_score = score;
}
	
int Score::getFistDigit()
{
	return s_digit1;
}
void Score::setFirstDigit(int first_digit)
{
	s_digit1 = first_digit;
}

int Score::getSecondDigit()
{
	return s_digit2;
}
void Score::setSecondDigit(int second_digit)
{
	s_digit2 = second_digit;
}

int Score::getThirdDigit()
{
	return s_digit3;
}
void Score::setThirdDigit(int third_digit)
{
	s_digit3 = third_digit;
}

int Score::getForthDigit()
{
	return s_digit4;
}
void Score::setForthDigit(int forth_digit)
{
	s_digit4 = forth_digit;
}

int Score::getFifthDigit()
{
	return s_digit5;
}
void Score::setFifthDigit(int fifth_digit)
{
	s_digit5 = fifth_digit;
}

int Score::getSixthDigit()
{
	return s_digit6;
}
void Score::setSixthDigit(int six_digit)
{
	s_digit6 = six_digit;
}