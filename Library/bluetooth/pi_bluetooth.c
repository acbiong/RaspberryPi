#include "pi_bluetooth.h"

scan_state Scan(char *addr, char *name)
{
	inquiry_info *ii = NULL;
	int max_rsp, num_rsp;
	int dev_id = 0;  //corresponding to the raspberry pi bluetooth ID
	int sock, len, flags;
	int i;
	char searchName[248] = {0};
	scan_state state = SCAN_SUCCESS;

	dev_id = hci_get_route(NULL);
	sock = hci_open_dev(dev_id);
	if (dev_id < 0 || sock < 0)
	{
		perror("opening socket");
		return SCAN_FAILED;
	}

	len = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	ii = (inquiry_info*) malloc(max_rsp * sizeof(inquiry_info));

	num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
	if (num_rsp < 0)
	{
		perror("hci_inquiry");
		return SCAN_FAILED;
	}

	for (i = 0; i < num_rsp; i++)
	{
		ba2str(&(ii + i)->bdaddr, addr);
		memset(searchName, 0, sizeof(searchName));
		if (hci_read_remote_name(sock, &(ii + i)->bdaddr, sizeof(searchName), searchName, 0)
				< 0)
			strcpy(searchName, "[unknown]");
		printf("%s  %s\n", addr, searchName);
		if(strcmp(name, searchName) == 0)
		{
			ba2str(&(ii + i)->bdaddr, addr);
			printf("Found!");
			state = SCAN_FOUND_SUCCESS;
		}
	}
	free(ii);
	close(sock);
	return state;
}

scan_state ScanBlocking(char *addr, char *name)
{
	scan_state state = Scan(addr, name);
	if(state == SCAN_FAILED)
	{
		return SCAN_FAILED;

	}
	while(state == SCAN_SUCCESS)
	{
		state = Scan(addr, name);
	}
	return SCAN_FOUND_SUCCESS;
}

int ClientSetup(char *dest, uint8_t port)
{
	struct sockaddr_rc addr = {0};
	int sock, status;
    // allocate a socket
    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) port;
    str2ba(dest, &addr.rc_bdaddr);

    // connect to server
    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    if(status == 0)  // connection success
    {
    	return sock;
    }
    else             // connection failure
    {
    	return status;
    }
}

int ServerSetup()
{
	struct sockaddr_rc loc_addr = {0};
	int sock;
	uint8_t port = 0;

	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	// bind socket to port 1 of the first available
	// local bluetooth adapter
	loc_addr.rc_family = AF_BLUETOOTH;
	loc_addr.rc_bdaddr = *BDADDR_ANY;
//    loc_addr.rc_channel = (uint8_t) port;
//    bind(sock, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

	if(DynamicBindRC(sock, &loc_addr, &port) < 0)
	{
		perror("Bind failed");
		return -1;
	}
	else
	{
		printf("Bind successfully to port: %d\n", port);
	}

	// put socket into listening mode
	listen(sock, port);

	return sock;
}

int ClientConnection(int sock)
{
	struct sockaddr_rc rem_addr = {0};
	char addr[1024] = {0};

	socklen_t opt = sizeof(rem_addr);
	int client = accept(sock, (struct sockaddr *)&rem_addr, &opt);

	ba2str(&rem_addr.rc_bdaddr, addr);
	printf("accepted connection from %s\n", addr);

	return client;
}

int ReadMessage(int sock, char *buf, int len)
{
	return read(sock, buf, len);
}

int SendMessage(int sock, char *buf, int len)
{
	return write(sock, buf, len);
}

int Close(int fd)
{
	return close(fd);
}

int DynamicBindRC(int sock, struct sockaddr_rc *sockaddr, uint8_t *port)
{
    int err = -1;
    for( *port = 1; *port <= 31; *port++ ) {
        sockaddr->rc_channel = *port;
        err = bind(sock, (struct sockaddr *)sockaddr, sizeof(*sockaddr));
        if( ! err || errno == EINVAL ) break;
    }
    if( *port == 31 ) {
        err = -1;
        errno = EINVAL;
    }
    return err;
}

