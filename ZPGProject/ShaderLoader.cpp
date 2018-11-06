#include "ShaderLoader.h"



ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

void ShaderLoader::loadShaders()
{
	for (Shader* shader : shaders) {
		shader->updateCameraPosition();
		shader->updateViewMatrix();
		shader->updateProjectionMatrix();
		shader->updateLight();
	}
}

void ShaderLoader::addShader(Shader * shader)
{
	shaders.push_back(shader);
}
