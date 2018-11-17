#pragma once
#include "Object.h"
#include <vector>

class Object;
class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();
	void addObject(Object * object);
	void drawObjects();

private:
	int index;
	std::vector<Object*> objects;
};

