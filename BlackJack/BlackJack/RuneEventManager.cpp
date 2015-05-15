#include "RuneEventManager.h"
#include "Includes\document.h"
using namespace rapidjson;
RuneEventManager* RuneEventManager::instance = 0;

RuneEventManager* RuneEventManager::Instance(){
	if (instance == nullptr){
		instance = new RuneEventManager();
	}
	return instance;
}
RuneEventManager::RuneEventManager(){

}
void RuneEventManager::RegisterRune(string rune, RuneEventListener* listener){
	if (runeEvents.count(rune) == 0){
		vector<RuneEventListener*> nrel = vector<RuneEventListener*>();
		runeEvents.insert(make_pair(rune, nrel));
	}
	runeEvents[rune].push_back(listener);
}
void RuneEventManager::DerigesterRune(string rune, RuneEventListener* listener){
	if (runeEvents.count(rune) != 0){
		vector<RuneEventListener*> list = runeEvents[rune];
		int index = find(list.begin(), list.end(), listener) - list.begin();
		list.erase(list.begin() + index);
	}
}
void RuneEventManager::ExectueRune(string rune){
	Document doc;
	doc.Parse<0>(rune.c_str());
	string type = doc["runeType"].GetString();
	if (runeEvents.count(type) > 0){
		vector<RuneEventListener*> events = runeEvents[type];
		for (int i = 0; i < events.size(); i++){
			events[i]->RuneCallback(type, rune);
		}
	}
}