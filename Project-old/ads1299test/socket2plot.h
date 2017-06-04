#ifndef _SOCKET2PLOT_H_
#define _SOCKET2PLOT_H_

#include "includes.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

typedef struct sock 
{
	int connection_fd;
	int socket_fd;
}socket4plot;

typedef enum
{
	OK,
	FAILED
}status_t;

status_t socketSetup(char *name, socket4plot *sock);
void closeSocket(socket4plot sock);
status_t sendSocket(socket4plot sock, char *buffer);

#endif