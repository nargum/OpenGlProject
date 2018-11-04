#include "Camera.h"



Camera::Camera()
{
	lastX = 0.f;
	lastY = 0.f;
	horizontal = -88.0f;
	vertical = 0.0f;
	firstMouse = true;
	camPosition = glm::vec3 (0.f, 0.f, 8.f);
	worldUP = glm::vec3 (0.f, 1.f, 0.f);
	camFront = glm::vec3 (0.f, 0.f, -1.f);
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	
}


Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::vec3 Camera::getCamPosition()
{
	return camPosition;
}

void Camera::moveForward()
{
	/*camPosition.z -= 0.05f;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);*/
	float cameraSpeed = 0.05f;
	camPosition += glm::normalize(camFront) * cameraSpeed;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	publishEvent();
}

void Camera::moveBack()
{
	/*camPosition.z += 0.05f;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);*/
	float cameraSpeed = 0.05f;
	camPosition -= cameraSpeed * camFront;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	publishEvent();
}

void Camera::moveLeft()
{
	/*camPosition.x -= 0.05f;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);*/
	float cameraSpeed = 0.05f;
	camPosition -= glm::normalize(glm::cross(camFront, worldUP)) * cameraSpeed;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	publishEvent();
}

void Camera::moveRight()
{
	/*camPosition.x += 0.05f;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);*/
	float cameraSpeed = 0.05f;
	camPosition += glm::normalize(glm::cross(camFront, worldUP)) * cameraSpeed;
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	publishEvent();
}

void Camera::moveCursor(double x, double y)
{
	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	

	float xOffset = x - lastX;
	float yOffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.2f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	horizontal += xOffset;
	vertical += yOffset;

	if (vertical > 89.0f)
		vertical = 89.0f;

	if (vertical < -89.0f)
		vertical = -89.0f;

	glm::vec3 temp;
	temp.x = cos(glm::radians(horizontal)) * cos(glm::radians(vertical));
	temp.y = sin(glm::radians(vertical));
	temp.z = sin(glm::radians(horizontal)) * cos(glm::radians(vertical));
	camFront = glm::normalize(temp);
	viewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUP);
	publishEvent();

}

float Camera::getXAngle()
{
	return horizontal;
}

void Camera::addListener(Listener * listener)
{
	listeners.push_back(listener);
}

void Camera::publishEvent()
{
	for (Listener* lis : listeners)
		lis->onEvent();
}


