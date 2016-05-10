/* Name : scoreLev0elControl.c	ver 1.0
 * Content : 게임 스코어(점수) 관리 및 레벨 관리 함수들의 정의
 * Implementation : KYS
 *
 * Last modified 2016/01/24
 */

#include "common.h"
#include "keyCurControl.h"
#include "TimeScoreLevelControl.h"


#define LEVEL_DIFF				5	// 단계별 속도 증가 정보
#define LEVEL_UP_SCORE_DIFF		20  // 레벨이 증가하는 스코어 간격 정보

static int curGameLevel = 1;
static int curGameScore = 0;
static unsigned int curTime, min, sec, timeBlocking;

/* 함	수 : void showCurrentScoreAndLevel(void)
 * 기	능 : 점수와 레벨 정보 출력
 * 반	환 : void
 *
 */
void showCurrentScoreAndLevel(void)
{	
	point curPos;
	curPos = GetCurrentCursorPos();

	SetCurrentCursorPos(34, 1);
	printf("▣ 다음 블록 ▣\n");

	SetCurrentCursorPos(30, 13);
	printf("▣ 현재 레벨 : %d    ▣", curGameLevel);

	SetCurrentCursorPos(30, 16);
	printf("▣ 현재 점수 : %d    ▣", curGameScore);

	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* 함	수 : void initTime(void)
* 기	능 : 시간 정보 초기화
* 반	환 : void
*
*/
void initTime(void)
{
	curTime = time(NULL);
	min = 0;
	sec = 0;
	timeBlocking = 0;
}

/* 함	수 : void ShowTime(void)
* 기	능 : 시간 정보 출력
* 반	환 : void
*
*/
void showTime(void)
{
	unsigned int newTime = (unsigned int)time(NULL);
	unsigned int diff = newTime - curTime;
	point curPos;
	time_t a = time(NULL);

	if (sec < diff)
	{
		curPos = GetCurrentCursorPos();
		sec = diff;

		if (sec == 30 && !timeBlocking)
		{
			gameLevelUp();
			timeBlocking = 1;
		}
		else if (sec == 60 && !timeBlocking)
		{
			curTime = time(NULL);
			min++;
			sec = 0;
			gameLevelUp();
			timeBlocking = 1;
		}
		else if(sec==31 || sec == 0)
			timeBlocking = 0;
		
		SetCurrentCursorPos(34, 10);
		printf("   %02d : %02d    ", min, sec);

		SetCurrentCursorPos(curPos.x, curPos.y);
	}	
}


/* 함	수 : void gameLevelUp(void)
* 기	능 : 게임 레벨 향상
* 반	환 : void
*
*/
void gameLevelUp(void)
{
	curGameLevel++;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* 함	수 : void addGameScore(int score)
* 기	능 : 게임 점수 향상
* 반	환 : void
*
*/
void addGameScore(int score)
{
	if (score < 1)
		return;

	curGameScore += score;
}