#include "Model.h"



Model::Model(Material mat)
{
	M = glm::mat4(1.0);
	material = mat;
}


Model::~Model()
{
}

glm::mat4 Model::getModelMatrix()
{
	return M;
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
	this->M = modelMatrix;
}

Material Model::getMaterial()
{
	return material;
}

void Model::translate(glm::vec3 distance)
{
	M = glm::translate(M, distance);
}

void Model::scale(float scale)
{
	M = glm::scale(M, glm::vec3(scale));
}

void Model::rotate(char axis, float angle)
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
