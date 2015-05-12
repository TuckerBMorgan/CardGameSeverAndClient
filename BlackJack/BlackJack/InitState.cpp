#include "InitState.h"
#include "RunningState.h"
#include "BlackJack.h"
#include "tcp.h"
#include "Includes\rapidjson.h"
#include "Includes\prettywriter.h"
#include "Includes\filestream.h"
#include "Includes\stringbuffer.h"
#include <guiddef.h>
#include <cstdio>
using namespace std;
using namespace rapidjson;

InitState::InitState(){

}
void InitState::Init(tcp* client){
	this->client = client;
	connected = client->init("127.0.0.1", 1337);
}
void InitState::enterState(){
	if (connected){
		cout << "Connected";
		Document newConc;
		char message[] = "{}";
		newConc.Parse<0>(message);
		Value type;
		type.SetString("newConnection");
		Value guid;
		guid.SetString("0c0c0c0c");
		newConc.AddMember("type", type, newConc.GetAllocator());
		newConc.AddMember("playerGuid", guid, newConc.GetAllocator());
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		newConc.Accept(writer);
		client->Send(buffer.GetString(), this);
	}
}
void InitState::exitState(){

}
void InitState::tick(){

}
void InitState::MessageCallback(string message){
	
	cout << "IT got to me";
	Document maybe;
	maybe.Parse<0>(message.c_str());
	string type = maybe["type"].GetString();
	if (type == "connected"){
		cout << " We are connected";
		RunningState* runningState = new RunningState();
		BlackJack::Instance()->PushState(runningState);
	}
}