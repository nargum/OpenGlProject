#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>



class Texture
{
public:
	Texture();
	~Texture();
	void bindTexture();

private:
	GLuint textureID;
};

