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
#include "RuneEventManager.h"
#define RuneEvent RuneEventManager::Instance()
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
		tcp::Instance()->Send(buffer.GetString());
		RuneEvent->RegisterRune("newConnection", this);
	}
}
void InitState::exitState(){

}
void InitState::tick(){

}
void InitState::RuneCallback(string runeType, string rune){
	

	if (runeType == "newConnection"){
		cout << " We are connected\n";
		RuneEvent->DerigesterRune("newConnection", this);
		RunningState* runningState = new RunningState();
		BlackJack::Instance()->PushState(runningState);
	}
}