#include "socket2plot.h"

#define UNIX_PATH_MAX 108

status_t socketSetup(char *name, socket4plot *sock)
{
	struct sockaddr_un address;
	int socket_fd, connection_fd;
	socklen_t address_length;
	//pid_t child;

	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		printf("socket() failed\n");
		return FAILED;
	}

	/*unlink("/tmp/demo_socket");*/
	unlink(name);
	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	/*snprintf(address.sun_path, UNIX_PATH_MAX, "/tmp/demo_socket");*/
	snprintf(address.sun_path, UNIX_PATH_MAX, name);

	if (bind(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un)) != 0) {
		printf("bind() failed\n");
		return FAILED;
	}
	if (listen(socket_fd, 5) != 0) {
		printf("listen() failed\n");
		return FAILED;
	}

	address_length = sizeof(address);
	int ii = 0;
	printf("Waiting for connection...\n");
	if ((connection_fd = accept(socket_fd,
		(struct sockaddr *) &address,
		&address_length)) > -1)
	{
		printf("Connected!\n");
		sock->connection_fd = connection_fd;
		sock->socket_fd = socket_fd;
		return OK;
		//while (1)
		//{
		//	bzero(buffer, 256);
		//	/*n = read(connection_fd, buffer, 255);
		//	if (n < 0) error("ERROR reading from socket");
		//	printf("Here is the message: %s\n\n", buffer);*/
		//	//strcpy(buffer, (char)ii);
		//	sprintf(buffer, "%d", ii);
		//	ii += 1;
		//	n = write(connection_fd, buffer, strlen(buffer));
		//	printf("Send %d\n", ii);
		//	if (n < 0)
		//		printf("ERROR writing to socket\n");
		//}
		//close(socket_fd);
		//close(socket_fd);
	}
}

void closeSocket(socket4plot sock)
{
	close(sock.socket_fd);
}

status_t sendSocket(socket4plot sock, char *buffer) 
{
	int n = write(sock.connection_fd, buffer, strlen(buffer));
	if (n < 0)
	{
		printf("ERROR writing to socket\n");
		return FAILED;
	}
}