#include "Model.h"



Model::Model(Material mat)
{
	modelMatrix = glm::mat4(1.0);
	material = mat;
}


Model::~Model()
{
}

glm::mat4 Model::getModelMatrix()
{
	return modelMatrix;
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

Material Model::getMaterial()
{
	return material;
}
