//============================================================================
// Name        : test-binary-protocol.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include "DeviceHiveEngine.h"
#include "communication.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int UsartSendBytes(unsigned char * data, int length) {
	return 0;
}
int BufferRecvBytes(unsigned char * data, int length) {
	return 0;
}


int main() {
	printf("heello\n");


	InitializeDeviceHive();
    SendRegMessage();

	return 0;
}
