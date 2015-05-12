#include "RunningState.h"
#include "tcp.h"
#include "Includes\stringbuffer.h"
#include "Includes\writer.h"
void RunningState::enterState(){
	Document docu;
	docu.Parse<0>("{}");
	Value type;
	Value guid;
	type.SetString("newPlayer");
	guid.SetString("0c0c0c0c");
	docu.AddMember("type", type, docu.GetAllocator());
	docu.AddMember("playerGuid", guid, docu.GetAllocator());
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	docu.Accept(writer);
	tcp::Instance()->Send(buffer.GetString(), this);
}
void RunningState::exitState(){

}
string CardFormatter(string rawCard){
	if (rawCard.length() != 2){
		return NULL;
	}
	char suit = rawCard[0];
	char value = rawCard[1];

}
void RunningState::tick(){
	cout << " Down Card" << CardFormatter(hand[0]);
	cout << "Up Card " << CardFormatter(hand[1]);
}
void RunningState::MessageCallback(std::string message){
	Document docu;
	docu.Parse<0>(message.c_str());
	if (docu["type"].GetString() == "newDeck"){
		Value& val = docu["payLoad"];
		hand.push_back(val["downCard"].GetString());
		hand.push_back(val["upCard"].GetString());
	}
	tick();
}