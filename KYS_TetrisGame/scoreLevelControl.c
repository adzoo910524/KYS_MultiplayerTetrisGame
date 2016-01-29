/* Name : scoreLev0elControl.c	ver 1.0
 * Content : 게임 스코어(점수) 관리 및 레벨 관리 함수들의 정의
 * Implementation : KYS
 *
 * Last modified 2016/01/24
 */
#include "common.h"
#include "keyCurControl.h"

#define LEVEL_DIFF				2	// 단계별 속도 증가 정보
#define LEVEL_UP_SCORE_DIFF		20  // 레벨이 증가하는 스코어 간격 정보

static int curGameLevel = 1;
static int curGameScore = 0;

/* 함	수 : void ShowCurrentScoreAndLevel(void)
 * 기	능 : 점수와 레벨 정보 출력
 * 반	환 : void
 *
 */
void ShowCurrentScoreAndLevel(void)
{
	SetCurrentCursorPos(34, 1);
	printf("▣ 다음 블록 ▣\n");

	SetCurrentCursorPos(30, 10);
	printf("▣ 현재 레벨 : %d    ▣", curGameLevel);

	SetCurrentCursorPos(30, 13);
	printf("▣ 현재 점수 : %d    ▣", curGameScore);
}

/* 함	수 : void GameLevelUp(void)
* 기	능 : 게임 레벨 향상
* 반	환 : void
*
*/
void GameLevelUp(void)
{
	curGameLevel++;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

/* 함	수 : void GameLevelUp(void)
* 기	능 : 게임 레벨 향상
* 반	환 : void
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