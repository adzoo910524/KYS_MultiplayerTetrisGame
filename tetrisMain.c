/* Name: tetrisMain.c  ver 1.2
 * Content: main �Լ��� ����
 * Implementation: KYS
 * 
 * Last modified 2016/01/24
 */
#include <Windows.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"
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
		puts("���α׷��� �����մϴ�.");
		exit(1);
	}
	system("cls");

    /* ���� �ӵ� ���� */
    InitKeyDelayRate(10);

    /* Ŀ�� ������ ���� */
    RemoveCursor();

    /* ���� ���� �׸��� */
    DrawGameBoard();
    
	/* ���� ����, ���� ǥ�� */
	ShowCurrentScoreAndLevel();

    /* �ݺ������� ���ο� ����� ���� */
    while(1)
    {
        /* �� ����� ������ġ ���� */
        InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);
        
        /* ��� ���� */
        ChooseBlock();
        
        /* ���� ���� Ȯ�� */
		if (IsGameOver())
		{
			setDefeatValue();
		}

		/* ���� ��� ä��� */
		DrawOpponentBlock();

		/* ���� ��� ��Ȳ ���� */
		if (NetworkConditionRenew(select) == 1)
		{
			SetCurrentCursorPos(10, 10);
			puts("You Win!");
			puts("");
			break;
		}
		else if (NetworkConditionRenew(select) == -1)
		{
			SetCurrentCursorPos(10, 10);
			puts("You Lose!");
			break;
		}
         
        /* ������ �۾� ���� */
        while(1)
        {
            /* ����� �Ʒ��� �� ĭ �̵� */
            if(BlockDown()==0) // ��� �̵� ���� �� 
                break;
            
            /* ���̸� Ű �Է� ó�� */
			if (ProcessKeyInput())
				break;		// SPACE �� �Է� ��
        }
    }

	NetworkClose();
    
    return 0;
}

/* end of file */