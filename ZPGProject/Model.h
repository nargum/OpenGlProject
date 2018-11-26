#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include <iostream>
#include <vector>
#include "Shader.h"
#include "Vertex.h"
#include "Object.h"
#include "AssimpVertex.h"
#include <string>

using namespace glm;

class Object;
class Shader;
class Model
{
public:
	Model(const Vertex *Vertices, float modelSize, float size);
	Model(const float *Vertices, float modelSize, float size);
	Model(std::string fileName);
	~Model();
	void bindVertexArray();
	float getModelSize();
	//void draw(Object* model);

private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	float modelSize;
	//Shader* shader;

};

