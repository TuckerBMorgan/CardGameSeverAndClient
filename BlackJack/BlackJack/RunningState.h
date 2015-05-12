#include "state.h"
#include <vector>

using namespace std;

class RunningState : public state{
	vector<string> hand;
public:
	void enterState() override;
	void exitState() override;
	void tick() override;
	void MessageCallback(string messsage) override;
};