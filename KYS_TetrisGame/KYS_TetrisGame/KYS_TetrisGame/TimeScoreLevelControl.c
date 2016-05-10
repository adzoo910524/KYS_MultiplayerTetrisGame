/* Name : scoreLev0elControl.c	ver 1.0
 * Content : ���� ���ھ�(����) ���� �� ���� ���� �Լ����� ����
 * Implementation : KYS
 *
 * Last modified 2016/01/24
 */

#include "common.h"
#include "keyCurControl.h"
#include "TimeScoreLevelControl.h"


#define LEVEL_DIFF				5	// �ܰ躰 �ӵ� ���� ����
#define LEVEL_UP_SCORE_DIFF		20  // ������ �����ϴ� ���ھ� ���� ����

static int curGameLevel = 1;
static int curGameScore = 0;
static unsigned int curTime, min, sec, timeBlocking;

/* ��	�� : void showCurrentScoreAndLevel(void)
 * ��	�� : ������ ���� ���� ���
 * ��	ȯ : void
 *
 */
void showCurrentScoreAndLevel(void)
{	
	point curPos;
	curPos = GetCurrentCursorPos();

	SetCurrentCursorPos(34, 1);
	printf("�� ���� ��� ��\n");

	SetCurrentCursorPos(30, 13);
	printf("�� ���� ���� : %d    ��", curGameLevel);

	SetCurrentCursorPos(30, 16);
	printf("�� ���� ���� : %d    ��", curGameScore);

	SetCurrentCursorPos(curPos.x, curPos.y);
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