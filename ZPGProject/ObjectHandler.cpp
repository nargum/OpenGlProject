#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	index = 0;
}


ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::addObject(Object * object)
{
	index++;
	object->setId(index);
	objects.push_back(object);
}

void ObjectHandler::drawObjects()
{
	for (Object* o : objects) {
		if(o->getDrawObject() == true)
			o->draw();
	}
}

void ObjectHandler::destroyObject(int index)
{
	for (Object* o : objects) {
		if (index == o->getId()) {
			o->setDrawObject(false);
			break;
		}
	}
}
