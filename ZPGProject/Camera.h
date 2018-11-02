#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <math.h>

#include <vector>
#include <iostream>
#include "Listener.h"
class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getCamPosition();
	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void moveCursor(double x, double y);
	float getXAngle();
	void addListener(Listener* listener);
	void publishEvent();
	void update();
	bool firstMouse;

private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 camFront;
	glm::vec3 worldUP;
	glm::vec3 camPosition;
	std::vector<Listener*> listeners;
	float horizontal;
	float vertical;
	float lastX;
	float lastY;
	
	
	
};

