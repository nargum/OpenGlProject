#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"
#include "Object.h"

class Object
{
public:
	Object(Material mat, GLuint id);
	~Object();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);
	Material getMaterial();
	void translate(glm::vec3 distance);
	void scale(float scale);
	void rotate(char axis, float angle);
	GLuint getId();
private:
	Material material;
	glm::mat4 M;
	GLuint id;
};

