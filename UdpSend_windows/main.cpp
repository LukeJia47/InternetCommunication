#include <Winsock2.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}

	//´´½¨Ì×½Ó×Ö
	SOCKET sockSen = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrRev;
	//addrRec.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrRev.sin_addr.S_un.S_addr = inet_addr("10.193.77.105");
	addrRev.sin_family = AF_INET;
	addrRev.sin_port = htons(1901);

	bind(sockSen, (SOCKADDR*)&addrRev, sizeof(addrRev));

	int len = sizeof(addrRev);
	char sendBuf[256];
	memset(sendBuf, '/0', sizeof(sendBuf));
	std::string message = "HK20211117100126K081";
	strcpy(sendBuf, message.c_str());
	while (1)
	{
		int send = sendto(sockSen, sendBuf, 256, 0, (SOCKADDR*)&addrRev, len);


		if (0 > send)
		{
			char str[100];
			itoa(WSAGetLastError(), str, 10);
			printf("%s\n", str);
		}
		else
			//printf("%d\t%s\n", recv, recvBuf);
			printf("%s%s\n", "send: ", sendBuf);
	}
	closesocket(sockSen);
	WSACleanup();
}


