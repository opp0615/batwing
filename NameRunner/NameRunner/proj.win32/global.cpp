#include "global.h"

int global_charSet = 0;// charSet 은 subway가 0 ring이 1 pinok가 2 livingdead가 3
int global_mapSet = 0;
int global_levelNumber = 0;

bool global_subwayState=1;//charState는 보유하고있는지 없는지를 판단한다 0이 없음 1이 있음 subway는 기본캐릭이므로 무조건 1
bool global_ringState=0;
bool global_pinokState=0;
bool global_livingDeadState=0;

bool global_soundSet = true;
bool global_bgmSet = true;