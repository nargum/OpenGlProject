#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include "Listener.h"

class Light
{
public:
	Light();
	~Light();
	glm::vec4 getLightPosition();
	void setLightPosition(glm::vec4 lightPosition);
	void setLightPosition(float angle);
	glm::vec4 getLightColor();
	void setLightColor(glm::vec4 lightColor);
	void addListener(Listener* listener);
	void publishEvent();

private:
	glm::vec4 lightPosition;
	glm::vec4 lightColor;
	std::vector <Listener*> listeners;
};

