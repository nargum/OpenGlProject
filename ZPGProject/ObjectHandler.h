#pragma once
#include <vector>
#include "Model.h"

class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();

private:
	int index;
	std::vector<Object*> objects;
};

