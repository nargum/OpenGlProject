#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Model
{
public:
	Model();
	~Model();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);
private:
	glm::mat4 modelMatrix;
};
