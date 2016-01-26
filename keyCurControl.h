/* Name: keyCurControl.h  ver 1.1
 * Content: 커서, 키보드 컨트롤 함수들의 정의
 * Implementation: KYS
 * 
 * Last modified 2016/01/24
 */

#ifndef __KEY_CURSOR_H_
#define __KEY_CURSOR_H_

#include "point.h"

void RemoveCursor(void);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(int x, int y);
int ProcessKeyInput(void);
void InitKeyDelayRate(int rate);
void KeyDelaySpeedCtl(int addSpeed);

void DrawSolidBlocks(void);
#endif
/* end of file */