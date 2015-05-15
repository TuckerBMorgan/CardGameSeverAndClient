#include "tcp.h"
#include "RuneEventManager.h"
int WNDSOCKET_ENDCHARACTER = -52;
#define RuneEvent RuneEventManager::Instance()
string findMessageInStream(char* stream, int streamLength){

	int count = 0;
	char value = stream[count];
	vector<char> newString;
	char stopCharacter = (char)WNDSOCKET_ENDCHARACTER;
	while (value != NULL && value != stopCharacter)
	{
		if (value == '\n' && stream[count + 1] == '\n'){
			break;
		}
		newString.push_back(value);
		count++;
		if (count < streamLength){
			value = stream[count];
		}
		else{
			cout << "Hello World";
		}
	}
	string returnStr = "";
	for (int i = 0; i < newString.size(); i++){
		returnStr += newString[i];
	}
	
	return returnStr;
}

tcp* tcp::instance = 0;
tcp* tcp::Instance(){
	if (!instance){
		instance = new tcp;
	}
	return instance;
}
void tcp::Send(string message){
	sendbuff = message;
}

void tcp::Write(){
	while (true){
		if (sendbuff != ""){
			int checkResult = send(ConnectSocket, sendbuff.c_str(), sendbuff.length(), 0);
			sendbuff = "";
		}
	}
}
void tcp::Read(){
	while (true){
		int checkResult = recv(ConnectSocket, recvbuff, recvbuflen, 0);
		if (checkResult > 0){
			string messageInString = findMessageInStream(recvbuff, recvbuflen);
			if (RuneEvent != NULL){
				RuneEvent->ExectueRune(messageInString);
			}
		}
		else if (checkResult == 0){
			closesocket(ConnectSocket);
			WSACleanup();
			return;
		}
	}
}
bool tcp::init(string address, int portNumber){
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 3), &wsaData);
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(address.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0){
		printf("getAddrInfo failed with error: %d\n", iResult);
		WSACleanup();
		return false;
	}
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next){
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET){
			printf("Socket failed with error: %d\n", WSAGetLastError());
			WSACleanup();
			return false;
		}
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR){
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);
	if (iResult == SOCKET_ERROR){
		printf("shutdown failed with error:%d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return false;
	}

	writing = new thread(&tcp::Write, this);
	reading = new thread(&tcp::Read, this);
	return true;
}