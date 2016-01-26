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

#define START_CURPOS_X         (5*2)
#define START_CURPOS_Y         (0)

int main(void)
{
	puts("Tetris Game");
	system("pause");
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
        if(IsGameOver())
            break;
         
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
    
    SetCurrentCursorPos(10, 10);
    puts("GAME OVER ^^");
    
    return 0;
}

/* end of file */