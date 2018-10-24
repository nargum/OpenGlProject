#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Object.h"
#include "Camera.h"
class Shader : Listener
{
public:
	Shader(Camera* camera, Object* object);
	~Shader();

	void sendUniform(const GLchar *name, glm::vec4 data);
	void updateModelMatrix(Object* object);
	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateLight();
	void updateCameraPosition();
	void useProgram();
	void onEvent();
	void bindVertexArray();

private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	Camera* camera;
	Object* object;
	void checkShaderCompilation();
};

