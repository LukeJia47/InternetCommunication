#include <Winsock2.h>
#include <stdio.h>
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

	SOCKET sockRec = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrRec;
	//addrRec.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrRec.sin_addr.S_un.S_addr =inet_addr("10.193.77.105");
	addrRec.sin_family = AF_INET;
	addrRec.sin_port = htons(1901);

	bind(sockRec, (SOCKADDR*)&addrRec, sizeof(addrRec));

	SOCKADDR_IN addrSen;
	int len = sizeof(addrSen);
	char recvBuf[256];
	memset(recvBuf, '/0', sizeof(recvBuf));
	while (1)
	{
		int recv=recvfrom(sockRec, recvBuf, 256, 0, (SOCKADDR*)&addrSen, &len);
		

		if (0 > recv)
		{
			char str[100];
			itoa(WSAGetLastError(), str, 10);
			printf("%s\n", str);
		}
		else
			//printf("%d\t%s\n", recv, recvBuf);
			printf("%s%s\n", "receive: ", recvBuf);
	}
	closesocket(sockRec);
	WSACleanup();
}


