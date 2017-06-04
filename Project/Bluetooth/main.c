#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "pi_bluetooth.h"

typedef union
{
	uint16_t pos;
	uint8_t pos_byte[2];

}Position;

int main()
{
    int sock = ServerSetup();
	if (sock > 0)
	{
		printf("Server setup successfully!\n");
	}
	else
	{
		printf("Server setup failed...exit\n");
		return 0;
	}

	int client = ClientConnection(sock);

	Position position;
	int len = 0;
	while (1)
	{
		printf("Please input the targeted position (uint16 type): ");
		scanf("%d", &position.pos);
		SendMessage(client, position.pos_byte, 2);
		len = ReadMessage(client, position.pos_byte, 2);
		printf("the position is %d\n", position.pos);
	}

}
