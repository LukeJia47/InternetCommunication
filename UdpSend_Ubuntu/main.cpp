//#include<sys/select.h>
//#include<unistd.h>
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<arpa/inet.h>
//#include<netinet/in.h>
//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//    int port = 63840;
//    int sockfd;
//
//    // 创建socket
//    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//    if(-1==sockfd)
//    {
//        return false;
//        puts("Failed to create socket");
//    }
//
//    // 设置地址与端口
//    struct sockaddr_in addr;
//    socklen_t  addr_len=sizeof(addr);
//
//    memset(&addr, 0, sizeof(addr));
//    addr.sin_family = AF_INET;       // Use IPV4
//    addr.sin_port   = htons(port);    //
//    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    addr.sin_addr.s_addr=inet_addr("10.193.77.105");
//
//    // Time out
//    struct timeval tv;
//    tv.tv_sec  = 0;
//    tv.tv_usec = 200000;  // 200 ms
//    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));
//
//    // 绑定获取数据的端口，作为发送方，不绑定也行
//    if (bind(sockfd, (struct sockaddr*)&addr, addr_len) == -1)
//    {
//        printf("Failed to bind socket on port %d\n", port);
//        close(sockfd);
//        return false;
//    }
//
//    int counter = 0;
//    string message="HK20211117100126K081";
//    char buff[1024];
//    strcpy(buff,message.c_str());
//
//    while(1)
//    {
//
//        addr.sin_family = AF_INET;
//        addr.sin_port   = htons(port);
//        addr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//        sendto(sockfd, buff, sizeof(buff), 0, (sockaddr*)&addr, addr_len);
//        printf("Sended %d\n", ++counter);
//        sleep(1);
//    }
//
//    close(sockfd);
//    return 0;
//}

//HK20211117100126K081

#include <string>
#include<arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h> /*包含socket()/bind()*/
#include <netinet/in.h> /*包含struct sockaddr_in*/
#include <string.h> /*包含memset()*/
#define PORT_SERV 1901 /*服务器端口*/
#define BUFF_LEN 256 /*缓冲区大小*/

#pragma comment(lib,"ws2_32.lib")

static void udpclie_echo(int s, struct sockaddr*to)
{

    char buff[BUFF_LEN]; /*发送给服务器的测试数据05 */
    char recvbuff[1024];
    struct sockaddr_in from; /*服务器地址*/
    socklen_t len = sizeof(*to); /*地址长度*/
    memset(&buff, '\0', sizeof(buff));
    std::string message="HK20211117100126K081";
    strcpy(buff,message.c_str());
    while(1){
        //scanf("%s",buff);
        int send=sendto(s, buff, BUFF_LEN, 0, to, len); /*发送给服务器*/
        //recvfrom(s, buff, BUFF_LEN, 0, (struct sockaddr*)&from, &len);
//sprintf(recvbuff,"%s this server return",buff); /*从服务器接收数据*/
       // printf("recved:%s\n",buff); /*打印数据*/
       //printf("发送%d\t%s\n",send,buff);
        printf("%s%s\n","send: ",buff);
    }
}


int main(int argc, char*argv[])
{
    int s; /*套接字文件描述符*/
    struct sockaddr_in addr_serv; /*地址结构*/

    s = socket(AF_INET, SOCK_DGRAM, 0); /*建立数据报套接字*/

    memset(&addr_serv, 0, sizeof(addr_serv)); /*清空地址结构*/
    addr_serv.sin_family = AF_INET; /*地址类型为AF_INET*/
/*addr_serv.sin_addr.s_addr = htonl(INADDR_ANY); 任意本地地址*/
//addr_serv.sin_addr.s_addr = inet_pton("192.168.19.152");
    addr_serv.sin_addr.s_addr = inet_addr("10.193.77.105");
    addr_serv.sin_port = htons(PORT_SERV); /*服务器端口*/

    udpclie_echo(s, (struct sockaddr*)&addr_serv); /*客户端回显程序*/

    close(s);
    return 0;
}
