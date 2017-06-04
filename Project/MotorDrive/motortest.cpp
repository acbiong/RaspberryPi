#include <stdio.h>
#include "serial.h"
#include "SCServo.h"
#include "pi_bluetooth.h"

int main()
{
        char device[20] = "/dev/ttyUSB0";
        SCServo servo(device, 115200);
        uint8_t ID = 1;

        //As a client
    	char addr[20] = {0};
    	int sock = -1;
    	int port = 1;
    	uint8_t time = 0;
    	printf("Scanning...\n");
    	while(ScanBlocking(addr, BRAINCO_PC) == SCAN_FOUND_SUCCESS)
    	{
        	sock = ClientSetup(addr, port);
        	while(sock < 0)
        	{
        		time ++;
        		printf("Connection failed!\n");
        		if(time > 5)
        		{
        			printf("Reconnection arrived at maximum times\n");
        			return 0;
        		}
        		printf("Reconnecting...\n");
        	}
            printf("connection success\n");
            char buf[1024] = { 0 };
			int len = 0;
			while (ReadMessage(sock, buf, sizeof(buf)))
			{
				int pos = buf[1]*256 + buf[0];
				printf("received: %d\n", pos);
				servo.WritePos(ID, pos, 0, 0);
				sleep(1);
				pos = servo.ReadPos(ID);
				printf("Position read is: %d\n", pos);
				buf[1] = pos >> 8;
				buf[0] = pos%256;
				len = SendMessage(sock, buf, 2);
				if(len <= 0)
				{
					perror("Sending failed");
					Close(sock);
					printf("Scanning...\n");
					break;
				}
			}
    	}

    	return 0;
}
