/* Name : scoreLev0elControl.c	ver 1.0
 * Content : ���� ���ھ�(����) ���� �� ���� ���� �Լ����� ����
 * Implementation : KYS
 *
 * Last modified 2016/01/24
 */

#include "common.h"
#include "keyCurControl.h"
#include "TimeScoreLevelControl.h"
#include <time.h>

#define LEVEL_DIFF				1	// �ܰ躰 �ӵ� ���� ����
#define LEVEL_UP_SCORE_DIFF		20  // ������ �����ϴ� ���ھ� ���� ����

static int curGameLevel = 1;
static int curGameScore = 0;
static time_t t = 0;;
static int curTime, min, sec, timeBlocking;

/* ��	�� : void showCurrentScoreAndLevel(void)
 * ��	�� : ������ ���� ���� ���
 * ��	ȯ : void
 *
 */
void showCurrentScoreAndLevel(void)
{	
	SetCurrentCursorPos(34, 1);
	printf("�� ���� ��� ��\n");

	SetCurrentCursorPos(30, 13);
	printf("�� ���� ���� : %d    ��", curGameLevel);

	SetCurrentCursorPos(30, 16);
	printf("�� ���� ���� : %d    ��", curGameScore);
}

/* ��	�� : void initTime(void)
* ��	�� : �ð� ���� �ʱ�ȭ
* ��	ȯ : void
*
*/
void initTime(void)
{
	curTime = time(NULL);
	min = 0;
	sec = 0;
	timeBlocking = 0;
}

/* ��	�� : void ShowTime(void)
* ��	�� : �ð� ���� ���
* ��	ȯ : void
*
*/
void showTime(void)
{
	int newTime = time(NULL);
	int diff = newTime - curTime;
	point curPos;

	if (sec < diff)
	{
		curPos = GetCurrentCursorPos();
		sec = diff;

		if (sec == 30 && !timeBlocking)
		{
			gameLevelUp();
			timeBlocking = 1;
		}
		else if (sec == 31)
			timeBlocking = 0;

		if (sec == 60 && !timeBlocking)
		{
			curTime = time(NULL);
			min++;
			sec = 0;
		}
		else if (sec == 1)
			timeBlocking = 0;
		
		SetCurrentCursorPos(32, 10);
		printf("   %02d : %02d    ", min, sec);

		SetCurrentCursorPos(curPos.x, curPos.y);
	}	
}


/* ��	�� : void gameLevelUp(void)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void gameLevelUp(void)
{
	curGameLevel++;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* ��	�� : void addGameScore(int score)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void addGameScore(int score)
{
	if (score < 1)
		return;

	curGameScore += score;
}