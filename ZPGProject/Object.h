#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"
#include "Object.h"
#include "Model.h"
#include "ObjectHandler.h"
#include "Texture.h"

class ObjectHandler;
class Model;
class Object
{
public:
	Object(Material mat, Texture* tex, Model* model, ObjectHandler* handler, Shader* shader);
	//Object(Material mat, Model* model, ObjectHandler* handler);
	~Object();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 modelMatrix);
	Material getMaterial();
	void translate(glm::vec3 distance);
	void scale(float scale);
	void rotate(char axis, float angle);
	GLuint getId();
	void setId(GLuint id);
	void draw();
	bool getDrawObject();
	void setDrawObject(bool drawObject);
	Texture* getTexture();
private:
	Material material;
	glm::mat4 M;
	GLuint id;
	Model* model;
	bool drawObject;
	Texture* texture;
	Shader* shader;
	void init(Material mat, Model* model, ObjectHandler* handler);
};

