#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class RuneEventListener{
public:
	virtual void RuneCallback(string runetype, string rune) = 0;
};
class RuneEventManager{

	public:
		static RuneEventManager* Instance();
		RuneEventManager();
		void RegisterRune(string, RuneEventListener*);
		void DerigesterRune(string, RuneEventListener*);
		void ExectueRune(string rune);
	private:
		unordered_map<string, vector<RuneEventListener*>> runeEvents;
		static RuneEventManager* instance;
};