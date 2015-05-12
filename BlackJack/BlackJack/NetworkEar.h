#pragma once
#include <string>
#include "Includes\document.h"
using namespace rapidjson;
class NetworkEar{
public:
	virtual void MessageCallback(std::string message) = 0;
};