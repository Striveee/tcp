#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//服务器端，被动连接方
int main()
{
	//创建套接字：IP地址  端口号     
    int	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	struct sockaddr_in  ser, cli;  //服务端，客户端
	memset(&ser, 0, sizeof(ser));  //清屏

	ser.sin_family  = AF_INET;  //地址簇协议
	ser.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP地址
	ser.sin_port = htons(6000);  //端口号，主机转网络

    //将服务器的ip地址+端口号与listenfd绑定
	int res = bind(listenfd,  (struct sockaddr *)&ser, sizeof(ser));
	assert(res != -1);   //  绑定失败：(1)IP地址不对;(2)端口号被占用或者没权限使用

    //创建监听队列，内核启动监听，接收客户端的连接
	//size = 5  表示内核维护的已完成三次握手的队列长度
	listen(listenfd, 5);
	//服务器接受不同客户端链接的循环
	while(1)
	{
        //记录客户端的地址信息
		int clilen = sizeof(cli);
        //获取一个与服务器连接完成的客户端
		int c = accept(listenfd, (struct sockaddr*)&cli, &clilen);
		assert(c != -1);

        while(1)
        {
            char buff[128] = {0};
            int n = recv(c, buff, 127, 0);  //接收数据
            if(n <= 0)
            {
                printf("one client unlink!\n");
                close(c);
                break;
            }
            printf("buff=%s\n", buff);
            send(c,"ok", 2, 0);  //发送数据
            close(listenfd);
        }
	}
}
