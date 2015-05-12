#pragma once
#include <string>
using namespace std;

class RuneEventManager{

	public:
		RuneEventManager();
		void RegisterManager();
		void BroadcastRune();
		void ExectueRune(string rune);
	private:

};