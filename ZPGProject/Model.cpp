#include "Model.h"



Model::Model()
{
	modelMatrix = glm::mat4(1.0);
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
