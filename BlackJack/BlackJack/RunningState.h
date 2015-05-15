#include "state.h"
#include <vector>

using namespace std;

class RunningState : public state{
private:
	vector<string> hand;
	bool moveLock;
public:
	void enterState() override;
	void exitState() override;
	void tick() override;
	void RuneCallback(string , string) override;
};