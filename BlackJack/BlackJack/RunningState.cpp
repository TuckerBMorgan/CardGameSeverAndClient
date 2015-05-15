#include "RunningState.h"
#include "tcp.h"
#include "Includes\stringbuffer.h"
#include "Includes\writer.h"
#include <iostream>
#include <string>

using namespace std;

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
	tcp::Instance()->Send(buffer.GetString());
	RuneEventManager::Instance()->RegisterRune("addCardToHand", this);
	moveLock = false;
}
void RunningState::exitState(){

}
int calculateHandValue(vector<string> currentHand){
	int value = 0;
	for (int i = 0; i < currentHand.size(); i++){
		string rawCard = currentHand[i];
		char val2 = rawCard[1];

		string formatted = "";
		switch (val2)
		{
		case 'a':
			value += 11;
			break;
		case 'k':
		case 'q':
		case 'j':
		case 't':
			value += 10;
			break;
		case '9':
			value += 9;
			break;
		case '8':
			value += 8;
			break;
		case '7':
			value += 7;
			break;
		case '6':
			value += 6;
			break;
		case '5':
			value += 5;
			break;
		case '4':
			value += 4;
			break;
		case '3':
			value += 3;
			break;
		case '2':
			value += 2;
			break;

		default:
			break;
		}

	}
	return value;
}
string CardFormatter(string rawCard){
	if (rawCard.length() < 2){
		return NULL;
	}
	char val1 = rawCard[0];
	char val2 = rawCard[1];
	char val3 = rawCard[3];

	string formatted = "";
	switch (val2)
	{
	case 'a':
		formatted = "Ace of";
		break;
	case 'k':
		formatted = "King of";
		break;
	case 'q':
		formatted = "Queen of";
		break;
	case 'j':
		formatted = "Jack of";
		break;
	case 't':
		formatted = "Ten of";
		break;
	case '9':
		formatted = "Nine of";
		break;
	case '8':
		formatted = "Eight of";
		break;
	case '7':
		formatted = "Seven of";
		break;
	case '6':
		formatted = "Six of";
		break;
	case '5':
		formatted = "Five of";
		break;
	case '4':
		formatted = "Four of";
		break;
	case '3':
		formatted = "Three of";
		break;
	case '2':
		formatted = "Two of";
		break;

	default:
		break;
	}

	switch (val1)
	{
	case 's':
		formatted += " Spades";
		break;
	case 'c':
		formatted += " Clubs";
		break;
	case 'h':
		formatted += " Hearts";
		break;
	case 'd':
		formatted += " Diamonds";
		break;

	default:
		break;
	}
	return formatted;
}


void RunningState::tick(){
	if (hand.size() < 2){
		return;
	}
	for (int i = 0; i < hand.size(); i++){
		if (i == 0){
			cout << "Down Card " << CardFormatter(hand[0]) << "\n";
		}
		else {
			cout << "Up Card " << CardFormatter(hand[i]) << "\n";
		}
	}
	cout << "Value of hand is " << calculateHandValue(hand) << "\n";

	cout << "What do you want to do next\n";
	cout << "H- Hit\n";
	cout << "F- Fold\n";
	cout << "S- Stay\n";
	char choice;
	cin >> choice;
	cout << choice;
	if (choice == 'H' || choice == 'h'){
		Document docu;
		docu.Parse<0>("{}");
		Value type;
		type.SetString("hit");
		docu.AddMember("type", type, docu.GetAllocator());
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		docu.Accept(writer);
		tcp::Instance()->Send(buffer.GetString());
		moveLock = true;
	}
	else if (choice == 'F' || choice == 'f'){

	}
	else if (choice == 'S' || choice == 's'){

	}
	else
	{
		tick();
	}


	while (moveLock)
	{

	}
}
void RunningState::RuneCallback(std::string runetype, string rune){
	
	if (runetype == "addCardToHand"){
		Document doc;
		doc.Parse<0>(rune.c_str());
		hand.push_back(doc["card"].GetString());
		moveLock = false;
	}
	tick();
}