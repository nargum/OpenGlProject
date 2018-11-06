#pragma once
#include <vector>
#include "Shader.h"

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();
	void loadShaders();
	void addShader(Shader* shader);

private:
	std::vector<Shader*> shaders;
};

