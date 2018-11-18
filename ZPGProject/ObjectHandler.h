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
	void destroyObject(int index);

private:
	int index;
	std::vector<Object*> objects;
};

