#pragma once
#include "state.h"
class tcp;
using namespace std;
class InitState : public state{
private:
	tcp* client;
	bool connected;
public:
	InitState();
	void Init(tcp* client);
	void enterState() override;
	void exitState() override;
	void tick() override;
	void MessageCallback(string message) override;
};