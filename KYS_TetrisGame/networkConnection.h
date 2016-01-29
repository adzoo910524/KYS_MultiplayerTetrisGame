/* Name: networkConnection.h  ver 1.0
* Content: UDP를 통한 네트워크 연결 함수들의 정의
* Implementation: KYS
*
* Last modified 2016/01/30
*/

#ifndef __NETWORK_CONNECTION_H__
#define __NETWORK_CONNECTION_H__

void BeServer(void);
void BeClient(void);
int NetworkConditionRenew(int SC_select);
void NetworkClose(void);
void ErrorHandling(char *message);

#endif