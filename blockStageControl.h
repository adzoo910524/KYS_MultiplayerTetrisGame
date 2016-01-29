/* Name: blockStageControl.h ver 1.2
 * Content: 블록, 게임화면 컨트롤 함수들의 선언
 * Implementation: KYS
 * 
 * Last modified 2016/01/24
 */

#ifndef __BLOCK_STAGE_H_
#define __BLOCK_STAGE_H_

void InitNewBlockPos(int x, int y);
void ChooseBlock(void);
int GetCurrentBlockIdx(void);
int GetNextBlockIdx(void);
void ShowBlock(char blockInfo[][4]);
void NextShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
int BlockDown(void);
void ShiftLeft(void);
void ShiftRight(void);
void RotateBlock(void);
void SolidCurrentBlock(void);

void AddCurrentBlockInfoToBoard(void);
void DrawGameBoard(void);
void DrawOpponentBlock(void);
int IsGameOver(void);
void setDefeatValue(void);

#endif