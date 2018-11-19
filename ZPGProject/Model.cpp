#include "Model.h"

Model::Model(Shader* shader, const Vertex *VERTICES, float modelSize, float size)
{
	this->modelSize = modelSize;
	this->shader = shader;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//this->VBO = VBO;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, VERTICES,
		GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	bindVertexArray();
	
}

Model::Model(Shader * shader, const float * VERTICES, float modelSize, float size)
{
	this->modelSize = modelSize;
	this->shader = shader;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//this->VBO = VBO;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, VERTICES,
		GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	bindVertexArray();
}


Model::~Model()
{
}


void Model::bindVertexArray()
{
	glBindVertexArray(VAO);
}

void Model::draw(Object* model)
{
	//std::cout << model->getId() << std::endl;
	
	//glStencilMask(0xFF);
	shader->useProgram();
	bindVertexArray();
	shader->updateModelMatrix(model->getModelMatrix());
	shader->updateMaterial(model->getMaterial());
	shader->updateViewMatrix();
	shader->updateProjectionMatrix();
	glStencilFunc(GL_ALWAYS, model->getId(), 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, modelSize);
	
}






