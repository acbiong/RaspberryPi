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
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 5555

typedef union
{
	uint16_t pos;
	uint8_t pos_byte[2];

}Position;

int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;
	char IP_Addr[]="192.168.77.57";

	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr((char*)IP_Addr);
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("connect");
		return 1;
	}
	printf("connect with destination host...\n");

	while(1)
	{
		Position SendPosition,RecvPosition;
		printf("Please input the targeted position (uint16 type): ");
		scanf("%d", &SendPosition.pos);
		printf("\n");

		int len = 0;
		send(clientSocket, (char*)SendPosition.pos_byte, 2, 0);
		len = recv(clientSocket, RecvPosition.pos_byte, 2, 0);
		printf("the position is %d\n", RecvPosition.pos);
	}
	close(clientSocket);
	return 0;
}
