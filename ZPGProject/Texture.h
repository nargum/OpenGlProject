#pragma once
#include <GL/glew.h>
#include <SOIL.h>


class Texture
{
public:
	Texture();
	~Texture();
	void bindTexture();

private:
	GLuint textureID;
};

