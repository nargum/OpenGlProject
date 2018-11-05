#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Camera.h"
#include "Light.h"
#include "Material.h"

class Shader : Listener
{
public:
	Shader(Camera* camera, Light* light);
	~Shader();

	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateLight();
	void updateCameraPosition();
	void updateMaterial(Material mat);
	void useProgram();
	void onEvent();
	void onLightEvent();
	void updateModelMatrix(glm::mat4 modelMatrix);

private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	Camera* camera;
	Light* light;
	void checkShaderCompilation();
};

