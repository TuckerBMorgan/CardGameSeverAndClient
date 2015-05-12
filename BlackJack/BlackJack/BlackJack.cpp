#include "BlackJack.h"
#include "InitState.h"
#include "tcp.h"
BlackJack* BlackJack::instance = 0;
BlackJack* BlackJack::Instance(){
	if (instance == 0){
		instance = new BlackJack();
	}
	return instance;
}
void BlackJack::Init(){
	InitState* initState = new InitState();
	initState->Init(tcp::Instance());
	PushState(initState);
}

void BlackJack::PopState(){
	currentState->exitState();
	delete &currentState;
	if (stateStack.size() > 0){
		state* newCurrent = stateStack.top();
		stateStack.pop();
		newCurrent->enterState();
	}
}
void BlackJack::PushState(state* newState){
	if (currentState == nullptr){
		currentState = newState;
	}
	else{
		stateStack.push(currentState);
		currentState = newState;
	}
	currentState->enterState();
}