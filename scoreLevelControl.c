/* Name : scoreLev0elControl.c	ver 1.0
 * Content : ���� ���ھ�(����) ���� �� ���� ���� �Լ����� ����
 * Implementation : KYS
 *
 * Last modified 2016/01/24
 */
#include "common.h"
#include "keyCurControl.h"

#define LEVEL_DIFF				2	// �ܰ躰 �ӵ� ���� ����
#define LEVEL_UP_SCORE_DIFF		20  // ������ �����ϴ� ���ھ� ���� ����

static int curGameLevel = 1;
static int curGameScore = 0;

/* ��	�� : void ShowCurrentScoreAndLevel(void)
 * ��	�� : ������ ���� ���� ���
 * ��	ȯ : void
 *
 */
void ShowCurrentScoreAndLevel(void)
{
	SetCurrentCursorPos(34, 1);
	printf("�� ���� ��� ��\n");

	SetCurrentCursorPos(30, 10);
	printf("�� ���� ���� : %d    ��", curGameLevel);

	SetCurrentCursorPos(30, 13);
	printf("�� ���� ���� : %d    ��", curGameScore);
}

/* ��	�� : void GameLevelUp(void)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void GameLevelUp(void)
{
	curGameLevel++;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* ��	�� : void GameLevelUp(void)
* ��	�� : ���� ���� ���
* ��	ȯ : void
*
*/
void AddGameScore(int score)
{
	if (score < 1)
		return;

	curGameScore += score;

	if (curGameScore >= curGameLevel * LEVEL_UP_SCORE_DIFF)
		GameLevelUp();
}