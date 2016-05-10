/* Name: networkConnection.c  ver 1.0
* Content: UDP를 통한 네트워크 연결 함수들의 정의
* Implementation: KYS
*
* Last modified 2016/01/30
*/
#include "common.h"
#include "blockStageControl.h"
#include "TimeScoreLevelControl.h"
#include "networkConnection.h"
#include <winsock2.h>


#define  GBOARD_WIDTH    10
#define  GBOARD_HEIGHT   20

#define OPPONENT_GBOARD_WIDTH    10
#define OPPONENT_GBOARD_HEIGHT   20

enum { WIN = 1, CONTINUE = 0, LOSE = -1 };

static WSADATA wsaData;
static SOCKET sock;
static SOCKADDR_IN servAdr, clntAdr;

static int strLen;
static int clntAdrSz;


extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
extern int opponentGameBoardInfo[OPPONENT_GBOARD_HEIGHT + 1][OPPONENT_GBOARD_WIDTH + 2];

static const int BUF_SIZE = sizeof(opponentGameBoardInfo);

/* 함    수: void BeServer(void)
* 기    능: Server 함수
* 반    환: void
*
*/
void BeServer(void)
{
	int myPort;
	u_long sock_on = 1;

	fputs("Port Number input : ", stdout);
	scanf("%d", &myPort);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("UDP socket creation error");

	ioctlsocket(sock, FIONBIO, &sock_on);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(myPort);

	if (bind(sock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	while (recv(sock, (char*)gameBoardInfo, BUF_SIZE, 0) == SOCKET_ERROR);
}

/* 함    수: void BeClient(void)
* 기    능: Client 함수
* 반    환: void
*
*/
void BeClient(void)
{
	int myPort;
	char myIP[30];
	u_long sock_on = 1;

	fputs("IP Address input : ", stdout);
	scanf("%s", myIP);
	fputs("Port Number input : ", stdout);
	scanf("%d", &myPort);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	ioctlsocket(sock, FIONBIO, &sock_on);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(myIP);
	servAdr.sin_port = htons(myPort);

	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	while (send(sock, (char*)gameBoardInfo, BUF_SIZE, 0) == SOCKET_ERROR);
}

/* 함    수: void NetworkConditionRenew(int SC_select)
* 기    능: 네트워크 상황 갱신 (상대방 화면)
* 반    환: int ( 승리 :1 / 진행중 : 0 )
*
*/
int NetworkConditionRenew(int SC_select)
{
	static unsigned int curTime = 0;
	unsigned int time_t = (unsigned int)time(NULL);

	if (gameBoardInfo[0][0] == -1) {
		sendto(sock, (char*)gameBoardInfo, BUF_SIZE, 0, (SOCKADDR*)&clntAdr, sizeof(clntAdr) == SOCKET_ERROR);
		return LOSE;
	}

	if (curTime != time_t) {
		curTime = time_t;
		if (SC_select == 1)
		{
			clntAdrSz = sizeof(clntAdr);
			while (recvfrom(sock, (char*)opponentGameBoardInfo, BUF_SIZE, 0,
				(SOCKADDR*)&clntAdr, &clntAdrSz) > 0);
			if (opponentGameBoardInfo[0][0] == LOSE) {
				DrawOpponentBlock();
				return WIN;
			}
			sendto(sock, (char*)gameBoardInfo, BUF_SIZE, 0,
				(SOCKADDR*)&clntAdr, sizeof(clntAdr));
		}
		else
		{
			while (recv(sock, (char*)opponentGameBoardInfo, BUF_SIZE, 0) > 0);
			if (opponentGameBoardInfo[0][0] == LOSE) {
				DrawOpponentBlock();
				return WIN;
			}
			send(sock, (char*)gameBoardInfo, BUF_SIZE, 0);
		}
	}

	return CONTINUE;
}

/* 함    수: void NetworkClose(void)
* 기    능: 네트워크 종료
* 반    환: void
*
*/
void NetworkClose(void)
{
	closesocket(sock);
	WSACleanup();
}

/* 함    수: void ErrorHandling(char *message)
* 기    능: 네트워크 예외처리
* 반    환: void
*
*/
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
/* end of file */