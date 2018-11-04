#include "Object.h"

Object::Object(Shader* shader, const Vertex *VERTICES, float modelSize, float size)
{
	this->modelSize = modelSize;
	this->shader = shader;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, VERTICES,
		GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	bindVertexArray();
}


Object::~Object()
{
}

void Object::rotate(char axis, float angle, Model* model)
{
	glm::mat4 M = glm::mat4(1.0f);
	switch (axis) {
	case 'x':
		M = glm::rotate(model->getModelMatrix(), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model->setModelMatrix(M);
		break;
	case 'y':
		M = glm::rotate(model->getModelMatrix(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		model->setModelMatrix(M);
		break;
	case 'z':
		M = glm::rotate(model->getModelMatrix(), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		model->setModelMatrix(M);
		break;
	}
}

void Object::translate(glm::vec3 distance, Model* model)
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(model->getModelMatrix(), distance);
	model->setModelMatrix(M);
}

void Object::scale(float scale, Model* model)
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(model->getModelMatrix(), glm::vec3(scale));
	model->setModelMatrix(M);
}

void Object::bindVertexArray()
{
	glBindVertexArray(VAO);
}

void Object::draw(Model* model)
{
	shader->useProgram();
	bindVertexArray();
	shader->updateModelMatrix(model->getModelMatrix());
	glDrawArrays(GL_TRIANGLES, 0, modelSize);
}






