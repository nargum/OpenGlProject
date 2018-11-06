#include "Light.h"



Light::Light()
{
	lightPosition = glm::vec4(0.0, 0.0, -3.0, 1.0);
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
	this->lightPosition = this->lightPosition + lightPosition;
	publishEvent();
}

void Light::setLightPosition(float angle)
{
	float x = this->lightPosition.x + cos(angle) * 20.0;
	this->lightPosition.x = x;
	float y = this->lightPosition.y + sin(angle) * 20.0;
	this->lightPosition.y = y;
	//this->lightPosition = glm::normalize(this->lightPosition);
	//this->lightPosition.x += angle;
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
