#include "tcp.h"
#include "InitState.h"
#include "BlackJack.h"
#include <iostream>

using namespace std;

int main(){
	BlackJack* blackJack;
	blackJack = new BlackJack();
	blackJack->Init();
	int i = 0;
	cin >> i;
	return 0;
}