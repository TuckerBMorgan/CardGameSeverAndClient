#pragma once
#include "RuneEventManager.h"
class state : public virtual RuneEventListener{
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void tick() = 0;
};