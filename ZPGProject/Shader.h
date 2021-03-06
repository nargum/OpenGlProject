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
#include "Texture.h"
#include <string>
#include <fstream>
using namespace std;

class Shader : Listener
{
public:
	Shader(Camera* camera, Light* light, string vertexShader, string fragmentShader);
	~Shader();

	void updateViewMatrix();
	void updateProjectionMatrix();
	void updateLight();
	void updateCameraPosition();
	void updateMaterial(Material mat);
	void updateTexture(Texture* texture);
	void useProgram();
	void onEvent();
	void onLightEvent();
	void updateModelMatrix(glm::mat4 modelMatrix);

private:
	GLuint vertexShader;
	GLuint fragmentShader;
	const char* vertex_shader;
	const char* fragment_shader;
	GLuint shaderProgram;
	Camera* camera;
	Light* light;
	void checkShaderCompilation();
	string loadFile(std::string fileName);
};

