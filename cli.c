/*************************************************************************
    > File Name: cli.c
    > Author: wangchen
    > Mail: w_chen1024@qq.com 
    > Created Time: Tue 08 Jan 2019 11:38:45 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	//服务器的IP地址  端口号
	struct sockaddr_in  ser;
	memset(&ser, 0, sizeof(ser));

	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);  //  服务器上对应服务进程的端口号
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");  //  服务器的IP地址

	int res = connect(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	while(1)
	{
		printf("please input: ");
		char buff[128] = {0};
		fgets(buff, 128, stdin);

		if(strncmp(buff, "end", 3) == 0)
		{
			close(sockfd);
			break;
		}

		send(sockfd, buff, strlen(buff)-1, 0);

		char recvbuff[128] = {0};
		int n = recv(sockfd, recvbuff, 127, 0);
		if(n <= 0)
		{
			close(sockfd);
			break;
		}

		printf("cli recvbuff= %s\n", recvbuff);
	}
}
