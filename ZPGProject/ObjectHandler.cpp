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
		o->draw();
	}
}
