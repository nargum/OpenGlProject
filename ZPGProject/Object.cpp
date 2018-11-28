#include "Object.h"


Object::Object(Material mat, Texture* tex, Model* model, ObjectHandler* handler, Shader* shader)
{
	texture = tex;
	this->shader = shader;
	init(mat, model, handler);
}

/*Object::Object(Material mat, Model * model, ObjectHandler * handler)
{
	init(mat, model, handler);
}*/

Object::~Object()
{
}

glm::mat4 Object::getModelMatrix()
{
	return M;
}

void Object::setModelMatrix(glm::mat4 modelMatrix)
{
	this->M = modelMatrix;
}

Material Object::getMaterial()
{
	return material;
}

void Object::translate(glm::vec3 distance)
{
	M = glm::translate(M, distance);
}

void Object::scale(float scale)
{
	M = glm::scale(M, glm::vec3(scale));
}

void Object::rotate(char axis, float angle)
{
	switch (axis) {
	case 'x':
		M = glm::rotate(M, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case 'y':
		M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'z':
		M = glm::rotate(M, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	}
}

GLuint Object::getId()
{
	return id;
}

void Object::setId(GLuint id)
{
	this->id = id;
}

void Object::draw()
{
	//model->draw(this);
	shader->useProgram();
	model->bindVertexArray();
	shader->updateModelMatrix(this->getModelMatrix());
	shader->updateMaterial(this->getMaterial());
	shader->updateViewMatrix();
	shader->updateProjectionMatrix();
	shader->updateTexture(this->getTexture());
	glStencilFunc(GL_ALWAYS, this->getId(), 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, model->getModelSize());
	//glDrawElements(GL_TRIANGLES, model->getModelSize(), GL_UNSIGNED_INT, NULL);
}

bool Object::getDrawObject()
{
	return drawObject;
}

void Object::setDrawObject(bool drawObject)
{
	this->drawObject = drawObject;
}

Texture * Object::getTexture()
{
	return texture;
}

void Object::init(Material mat, Model * model, ObjectHandler * handler)
{
	drawObject = true;
	M = glm::mat4(1.0);
	material = mat;
	this->model = model;
	handler->addObject(this);
}
