#ifndef _PI_BLUETOOTH_H_
#define _PI_BLUETOOTH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <string.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"{
#endif

#define BRAINCO_PC "brainco-OptiPlex-5040-0"    //Bifei's PC
#define RASPI      "raspberrypi"

typedef enum
{
	SCAN_FAILED = -1,
	SCAN_SUCCESS,
	SCAN_FOUND_SUCCESS,
}scan_state;

scan_state Scan(char *addr, char *name);
scan_state ScanBlocking(char *addr, char *name);
int ClientSetup(char *dest, uint8_t port);
int ServerSetup();
int ClientConnection(int sock);
int ReadMessage(int sock, char *buf, int len);
int SendMessage(int sock, char *buf, int len);
int Close(int fd);
int DynamicBindRC(int sock, struct sockaddr_rc *sockaddr, uint8_t *port);

#ifdef __cplusplus
}
#endif

#endif
