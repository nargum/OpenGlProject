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
#include "Shader.h"
#include "Vertex.h"
#include "Model.h"

class Shader;
class Object
{
public:
	Object(Shader* shader, const Vertex *Vertices, float modelSize, float size);
	~Object();

	/*void rotate(char axis, float angle, Model* model);
	void translate(glm::vec3 distance, Model* model);
	void scale(float scale, Model* model);*/
	void bindVertexArray();
	void draw(Model* model);

private:
	GLuint VAO;
	GLuint VBO;
	float modelSize;
	Shader* shader;

};

