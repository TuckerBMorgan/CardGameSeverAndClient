#pragma once
#include "state.h"
#include <vector>
#include <stack>

using namespace std;

class BlackJack{

private:
	state* currentState;
	static BlackJack* instance;
	stack<state*> stateStack;
public:
	void Init();
	void PopState();
	void PushState(state* newState);
	static BlackJack* Instance();
};