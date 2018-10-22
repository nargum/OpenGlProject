#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include "Listener.h"

class Object
{
public:
	Object();
	~Object();

	glm::mat4 getModelMatrix();
	void rotate(char axis, float angle);
	void translate(glm::vec3 distance);
	void scale(float scale);
	void bindVertexArray();
	float getModelSize();
	void addListener(Listener* listener);
	void publishEvent();

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 M = glm::mat4(1.0f);
	float modelSize;
	std::vector<Listener*> listeners;

};

