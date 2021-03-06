/* Name: tetrisMain.c  ver 1.2
 * Content: main 함수의 정의
 * Implementation: KYS
 * 
 * Last modified 2016/01/24
 */
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#include <Windows.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "TimeScoreLevelControl.h"
#include "networkConnection.h"

#define START_CURPOS_X         (5*2)
#define START_CURPOS_Y         (0)

int main(void)
{
	int select;

	puts("Tetris Game");
	puts("Server : 1, Client : 2, Exit : 0");
	scanf("%d", &select);

	if (select == 1)
		BeServer();
	else if (select == 2)
		BeClient();
	else
	{
		puts("프로그램을 종료합니다.");
		exit(1);
	}
	system("cls");

    /* 게임 속도 설정 */
    InitKeyDelayRate(5);

    /* 커서 깜빡임 제거 */
    RemoveCursor();

    /* 게임 보드 그리기 */
    DrawGameBoard();
    
	/* 현재 점수, 레벨 표시 */
	showCurrentScoreAndLevel();

	/* 시간 정보 초기화 */
	NetworkConditionRenew(select);
	initTime();

    /* 반복적으로 새로운 블록의 등장 */
    while(1)
    {
        /* 새 블록의 등장위치 설정 */
        InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);

        /* 블록 선택 */
        ChooseBlock();

		/* 점수와 레벨 정보 출력 */
		showCurrentScoreAndLevel();
        
        /* 내리는 작업 시작 */
        while(1)
        {
			/* 시간 갱신 */
			showTime();

			/* 게임 종료 확인 */
			if (IsGameOver())
			{
				setLoseValue();
				NetworkConditionRenew(select);
				SetCurrentCursorPos(10, 10);
				puts("You Lose!");
				NetworkClose();
				return 0;
			}

			/* 상대방 블록 채우기 */
			DrawOpponentBlock();

			/* 상대방 블록 상황 갱신 */
			if (NetworkConditionRenew(select) == 1)
			{
				SetCurrentCursorPos(10, 10);
				puts("You Win!");
				NetworkClose();
				getchar();
				return 0;	
			}

            /* 블록을 아래로 한 칸 이동 */
            if(BlockDown()==0) // 블록 이동 실패 시 
                break;
            
            /* 게이머 키 입력 처리 */
			if (ProcessKeyInput())
				break;		// SPACE 바 입력 시
        }
    }
}

/* end of file */