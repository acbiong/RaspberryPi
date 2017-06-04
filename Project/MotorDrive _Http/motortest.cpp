#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "serial.h"
#include "SCServo.h"

#define SERVER_PORT 5555

int main()
{
	char device[20] = "/dev/ttyUSB0";
	SCServo servo(device, 115200);
	uint8_t ID = 1;

	//As a server
	int serverSocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int addr_len = sizeof(clientAddr);
	int client;
	char buffer[10];
	int iDataNum;

	//int socket(int domain, int type, int protocol);
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect");
		return 1;
	}
	//set socket listen
	if(listen(serverSocket, 5) < 0)
	{
		perror("listen");
		return 1;
	}

	while(1)
	{
		printf("Listening on port: %d\n", SERVER_PORT);
		client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
		if(client < 0)
		{
			perror("accept");
			continue;
		}
		printf("recv client data...\n");
		printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr));
		printf("Port is %d\n", htons(clientAddr.sin_port));
		while(1)
		{
			iDataNum = recv(client, buffer, 2, 0);
			if(iDataNum < 0)
			{
				perror("recv");
				continue;
			}
			int pos = (buffer[1]<<8) + buffer[0];
			printf("Received: %d\n", pos);
			servo.WritePos(ID, pos, 0, 0);
			sleep(1);
			pos = servo.ReadPos(ID);
			printf("Position read is: %d\n", pos);
			buffer[1] = pos >> 8;
			buffer[0] = pos & 0xFF;
			send(client, buffer, 2, 0);

			//FIXME need add exit socket function
		}
	}
	return 0;
}
