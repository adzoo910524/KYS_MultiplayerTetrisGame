/* Name: blockStageControl.c ver 1.2
 * Content: ���, ����ȭ�� ��Ʈ�� �Լ����� ����
 * Implementation: KYS
 * 
 * Last modified 2016/01/24
 */

#include <time.h>
#include "common.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include "TimeScoreLevelControl.h"
#include "blockStageControl.h"

#define  GBOARD_WIDTH    10
#define  GBOARD_HEIGHT   20
#define  GBOARD_ORIGIN_X  4
#define  GBOARD_ORIGIN_Y  2

#define  NEXT_GBOARD_WIDTH    5
#define  NEXT_GBOARD_HEIGHT   5
#define  NEXT_GBOARD_ORIGIN_X  34
#define  NEXT_GBOARD_ORIGIN_Y  2

#define OPPONENT_GBOARD_WIDTH    10
#define OPPONENT_GBOARD_HEIGHT   20
#define OPPONENT_GBOARD_ORIGIN_X  54
#define OPPONENT_GBOARD_ORIGIN_Y  2

#define TRUE	1
#define FALSE	0

int gameBoardInfo[GBOARD_HEIGHT+1][GBOARD_WIDTH+2]={0,};
extern int opponentGameBoardInfo[OPPONENT_GBOARD_HEIGHT + 1][OPPONENT_GBOARD_WIDTH + 2] = { 0, };

static int currentBlockModel, nextBlockModel;
static int curPosX, curPosY;
static int rotateSte;
static int timePlusValue = 0;
static int isFirstBlock = TRUE;

/* ��    ��: void InitNewBlockPos(int x, int y)
 * ��    ��: ����� ù ��ġ ����
 * ��    ȯ: void
 *
 */
void InitNewBlockPos(int x, int y)
{
    if(x<0 || y<0)
        return;
   
    curPosX=x;
    curPosY=y;

    SetCurrentCursorPos(x, y);
}

/* ��    ��: void ChooseBlock(void)
 * ��    ��: ����� ����� ������ ����
 * ��    ȯ: void
 *
 */
void ChooseBlock(void)
{
    srand((unsigned int)time(NULL)+ (timePlusValue++));
	if(!isFirstBlock)
	{ 
		currentBlockModel = nextBlockModel;
		nextBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
		NextShowBlock(blockModel[nextBlockModel]);
	}
	else
	{
		currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
		srand((unsigned int)time(NULL)+1);
		nextBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
		isFirstBlock = FALSE;
	}
	timePlusValue = (timePlusValue == 10 ? 0 : timePlusValue);
}

/* ��    ��: int GetCurrentBlockIdx(void)
 * ��    ��: ���� ����ؾ� �ϴ� ����� index ���� ��ȯ
 * ��    ȯ: int
 *
 */
int GetCurrentBlockIdx(void)
{
    return currentBlockModel + rotateSte;
}

/* ��    ��: int GetNextBlockIdx(void)
* ��    ��: ������ ����ؾ� �ϴ� ����� index ���� ��ȯ
* ��    ȯ: int
*
*/
int GetNextBlockIdx(void)
{
	return nextBlockModel + rotateSte;
}


/* ��    ��: void ShowBlock(char blockInfo[][4])
 * ��    ��: ���޵� ���ڸ� �����Ͽ� ��� ���
 * ��    ȯ: void
 *
 */
void ShowBlock(char blockInfo[][4])
{
    int y, x;
    point curPos=GetCurrentCursorPos();

    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            SetCurrentCursorPos(curPos.x+x*2, curPos.y+y);
            
            if(blockInfo[y][x] == 1)
                printf("��");
        }
    }
    SetCurrentCursorPos(curPos.x, curPos.y);
}

/* ��    ��: void NextShowBlock(void)
* ��    ��: ������ ����� ����� �׸���.
* ��    ȯ: void
*
*/
void NextShowBlock(char blockInfo[][4])
{
	int y, x;
	point orgPos;
	point curPos;
	orgPos = GetCurrentCursorPos();

	SetCurrentCursorPos(38, 3);
	curPos = GetCurrentCursorPos();

	for (y = 0; y<4; y++)
	{
		for (x = 0; x<4; x++)
		{
			SetCurrentCursorPos(curPos.x + x * 2, curPos.y + y);

			if (blockInfo[y][x] == 1)
				printf("��");
			else
				printf("��");
		}
	}

	SetCurrentCursorPos(orgPos.x, orgPos.y);
}

/* ��    ��: void DeleteBlock(char blockInfo[][4])
 * ��    ��: ���� ��ġ�� ��µ� ��� ����
 * ��    ȯ: void
 *
 */
void DeleteBlock(char blockInfo[][4])
{
    int y, x;
    point curPos=GetCurrentCursorPos();
    
    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            SetCurrentCursorPos(curPos.x+x*2, curPos.y+y);
            
            if(blockInfo[y][x] == 1)
                printf("  ");
        }
    }
    SetCurrentCursorPos(curPos.x, curPos.y);
}

/* ��    ��: int DetectCollision(int posX, int posY, char blockModel[][4])
 * ��    ��: ����� �̵� �� ȸ�� ���� ���� �Ǵ�
 * ��    ȯ: �̵� �� ȸ�� ���ɽ� 1 ��ȯ
 *
 */
int DetectCollision(int posX, int posY, char blockModel[][4])
{
    int x, y;

    /* gameBoardInfo �迭�� ��ǥ�� ���� */
    int arrX= (posX-GBOARD_ORIGIN_X)/2;
    int arrY= posY-GBOARD_ORIGIN_Y;

    /* �浹 �˻� */
    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            /* Short Circuit Evaluation�� ���� �迭 �Ϻθ� �˻� */
            if(blockModel[y][x]==1 && gameBoardInfo[arrY+y][arrX+x]==1)
                return 0;
        }
    }
    
    return 1;
}

/* ��    ��: void RemoveFillUpLine(void)
* ��    �� : �� ������ ä���� ����� �����Ѵ�.
* ��    ȯ: void
*
*/
void RemoveFillUpLine(void)
{
	int x, y;
	int line;

	for (y = GBOARD_HEIGHT - 1; y > 0; y--)
	{
		for (x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			if (gameBoardInfo[y][x] != 1)
				break;
		}

		if (x == (GBOARD_WIDTH + 1))	// ������ �� ä�����ٸ�
		{
			for (line = 0; y - line > 0; line++)
			{
				memcpy(&gameBoardInfo[y - line][1], &gameBoardInfo[(y - line) - 1][1], GBOARD_WIDTH*sizeof(int));
			}

			y++;
			addGameScore(10);
		}
	}

	DrawSolidBlocks();
}

/* ��    ��: int BlockDown(void)
 * ��    ��: ����Ϳ� �׷��� ����� �Ʒ��� �� ĭ ����
 * ��    ȯ: ���� �� 1, ���� �� 0
 *
 */
int BlockDown(void)
{
	if (!DetectCollision(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()]))
	{
		/* �� ������ ä���� ��� ���� �˻� */
		AddCurrentBlockInfoToBoard();
		RemoveFillUpLine();
		return 0;
	}
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosY+=1;
    
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);

    return 1;
}

/* ��    ��: void ShiftLeft(void)
 * ��    ��: ����� �������� �� ĭ �̵�
 * ��    ȯ: void
 *
 */
void ShiftLeft(void)
{
    if(!DetectCollision(curPosX-2, curPosY, blockModel[GetCurrentBlockIdx()]))
      return;
 
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosX-=2;
    
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/* ��    ��: void ShiftRight(void)
 * ��    ��: ����� ���������� �� ĭ �̵�
 * ��    ȯ: void
 *
 */
void ShiftRight(void)
{
    if(!DetectCollision(curPosX+2, curPosY, blockModel[GetCurrentBlockIdx()]))
        return;
 
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosX+=2;
    
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/* ��    ��: void RotateBlock(void)
 * ��    ��: ����� 90�� ȸ��
 * ��    ȯ: void
 *
 */
void RotateBlock(void)
{
    int nextRotSte;
    int beforeRotSte=rotateSte;  // ������ ���� ����
    
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);

    nextRotSte=rotateSte+1;
    nextRotSte%=4;
    rotateSte=nextRotSte;

    if(!DetectCollision(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
    {
        rotateSte=beforeRotSte;
        return;
    }
    
    SetCurrentCursorPos(curPosX, curPosY);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/* ��    ��: void DrawGameBoard(void)
 * ��    ��: ���� ���� ��� ���� �׸���.
 * ��    ȯ: void
 *
 */
void DrawGameBoard(void)
{
    int x, y;

    /* �ð����� �κ� ó�� */

	SetCurrentCursorPos(11, 23);
	printf("My Screen");

	//// Block Board /////
    for(y=0; y<=GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y+y);

        if(y==GBOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }
    
    for(y=0; y<=GBOARD_HEIGHT; y++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X+(GBOARD_WIDTH+1)*2, GBOARD_ORIGIN_Y+y);

        if(y==GBOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }
    
    for(x=1; x<GBOARD_WIDTH+1; x++)
    {
        SetCurrentCursorPos(GBOARD_ORIGIN_X+x*2, GBOARD_ORIGIN_Y+GBOARD_HEIGHT);
        printf("��");
    }

	//// Next Block Board /////

	for (y = 0; y <= NEXT_GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(NEXT_GBOARD_ORIGIN_X, NEXT_GBOARD_ORIGIN_Y + y);

		if (y == NEXT_GBOARD_HEIGHT)
			printf("��");
		else if (y == 0)
			printf("��");
		else
			printf("��");
	}

	for (y = 0; y <= NEXT_GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(NEXT_GBOARD_ORIGIN_X + (NEXT_GBOARD_WIDTH + 1) * 2, NEXT_GBOARD_ORIGIN_Y + y);

		if (y == NEXT_GBOARD_HEIGHT)
			printf("��");
		else if (y == 0)
			printf("��");
		else
			printf("��");
	}

	for (x = 1; x<NEXT_GBOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(NEXT_GBOARD_ORIGIN_X + x * 2, NEXT_GBOARD_ORIGIN_Y + NEXT_GBOARD_HEIGHT);
		printf("��");
	}

	for (x = 1; x<NEXT_GBOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(NEXT_GBOARD_ORIGIN_X + x * 2, NEXT_GBOARD_ORIGIN_Y);
		printf("��");
	}


	//// Opponent Block Board /////
	SetCurrentCursorPos(59, 23);
	printf("Opponent Screen");
	for (y = 0; y <= OPPONENT_GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(OPPONENT_GBOARD_ORIGIN_X, OPPONENT_GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}

	for (y = 0; y <= OPPONENT_GBOARD_HEIGHT; y++)
	{
		SetCurrentCursorPos(OPPONENT_GBOARD_ORIGIN_X + (OPPONENT_GBOARD_WIDTH + 1) * 2, OPPONENT_GBOARD_ORIGIN_Y + y);

		if (y == OPPONENT_GBOARD_HEIGHT)
			printf("��");
		else
			printf("��");
	}

	for (x = 1; x<OPPONENT_GBOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(OPPONENT_GBOARD_ORIGIN_X + x * 2, OPPONENT_GBOARD_ORIGIN_Y + OPPONENT_GBOARD_HEIGHT);
		printf("��");
	}


    SetCurrentCursorPos(0, 0);	

    /* ������ �κ� ó�� */
    for(y=0; y<GBOARD_HEIGHT; y++)
    {
        gameBoardInfo[y][0]=1;
        gameBoardInfo[y][GBOARD_WIDTH+1]=1;
    }
    
    for(x=0; x<GBOARD_WIDTH+2; x++)
    {
        gameBoardInfo[GBOARD_HEIGHT][x]=1;
    }

}

/* ��    ��: void AddCurrentBlockInfoToBoard(void)
 * ��    ��: �迭�� ���� ����� ������ �߰��Ѵ�.
 * ��    ȯ: void
 *
 */
void AddCurrentBlockInfoToBoard(void)
{
    int x, y;

    int arrCurX;
    int arrCurY;
    
    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            /* Ŀ�� ��ġ ������ �迭 index ������ ���� */
            arrCurX=(curPosX-GBOARD_ORIGIN_X)/2;
            arrCurY=curPosY-GBOARD_ORIGIN_Y;

            if(blockModel[GetCurrentBlockIdx()][y][x]==1)
                gameBoardInfo[arrCurY+y][arrCurX+x]=1;
        }
    }
}

/* ��    ��: int IsGameOver(void)
 * ��    ��: ������ ����Ǿ����� Ȯ���ϴ� �Լ�
 * ��    ȯ: ���� ���� �� 1 ��ȯ
 *
 */
int IsGameOver(void)
{
    if(!DetectCollision(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
        return 1;
    else
        return 0;	 
}


/* ��    ��: void DrawSolidBlocks(void)
* ��    ��: ���� �ǿ� ������ ����� �׸���.
* ��    ȯ: void
*
*/
void DrawSolidBlocks(void)
{
	int x, y;
	int cursX, cursY;

	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		for (x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X;
			cursY = y + GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(cursX, cursY);

			if (gameBoardInfo[y][x] == 1)
				printf("��");
			else
				printf("  ");
		}
	}
}

/* ��    ��: void DrawOpponentBlock(void)
* ��    �� : ���� ��� ä���
* ��    ȯ: void
*
*/
void DrawOpponentBlock(void)
{
	int x, y;
	int cursX, cursY;

	point curPos = GetCurrentCursorPos();

	for (y = 0; y < OPPONENT_GBOARD_HEIGHT; y++)
	{
		for (x = 1; x < OPPONENT_GBOARD_WIDTH + 1; x++)
		{
			cursX = x * 2 + OPPONENT_GBOARD_ORIGIN_X;
			cursY = y + OPPONENT_GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(cursX, cursY);

			if (opponentGameBoardInfo[y][x] == 1)
				printf("��");
			else
				printf("  ");
		}
	}

	SetCurrentCursorPos(curPos.x, curPos.y);
}

/* ��    ��: void SolidCurrentBlock(void)
* ��    �� : �� ������ ä���� ����� �����Ѵ�.
* ��    ȯ: void
*
*/
void SolidCurrentBlock(void)
{
	while (BlockDown());
}

/* ��    ��: void setLoseValue()
* ��    ��: �й� �� �й� �� ����
* ��    ȯ: void
*
*/
void setLoseValue()
{
	gameBoardInfo[0][0] = -1;
}
/* end of file */