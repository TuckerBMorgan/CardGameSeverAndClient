#pragma once
#include "NetworkEar.h"
class state : public virtual NetworkEar{
public:
	virtual void enterState() = 0;
	virtual void exitState() = 0;
	virtual void tick() = 0;
};