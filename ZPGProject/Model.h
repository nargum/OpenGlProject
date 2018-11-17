#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <iostream>
#include <vector>
#include "Shader.h"
#include "Vertex.h"
#include "Object.h"

class Object;
class Shader;
class Model
{
public:
	Model(Shader* shader, const Vertex *Vertices, float modelSize, float size);
	~Model();
	void bindVertexArray();
	void draw(Object* model);

private:
	GLuint VAO;
	GLuint VBO;
	float modelSize;
	Shader* shader;

};

