#pragma once
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1337"

// < includes
#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <unordered_map>

// " includes
#pragma once
#include "NetworkEar.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
using namespace std;

class tcp{
public:
	static tcp* Instance();
	bool init(string addfress, int portNumber);
	void Send(string message);
private:
	int portNumber;
	thread* writing;
	thread* reading;
	static tcp* instance;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;
	char recvbuff[DEFAULT_BUFLEN];
	int iResult;
	string sendbuff;
	int recvbuflen = DEFAULT_BUFLEN;
	void Write();
	void Read();
	NetworkEar* currentEar;
};