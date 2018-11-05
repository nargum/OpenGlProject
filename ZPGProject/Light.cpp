#include "Light.h"



Light::Light()
{
	lightPosition = glm::vec4(0.0, 0.0, 3.0, 1.0);
	lightColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	publishEvent();
}


Light::~Light()
{
}

glm::vec4 Light::getLightPosition()
{
	return lightPosition;
}

void Light::setLightPosition(glm::vec4 lightPosition)
{
	this->lightPosition = lightPosition;
	publishEvent();
}

glm::vec4 Light::getLightColor()
{
	return lightColor;
}

void Light::setLightColor(glm::vec4 lightColor)
{
	this->lightColor = lightColor;
	publishEvent();
}

void Light::addListener(Listener * listener)
{
	listeners.push_back(listener);
}

void Light::publishEvent()
{
	for (Listener* lis : listeners) {
		lis->onLightEvent();
	}
}
