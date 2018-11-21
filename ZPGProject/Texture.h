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
	unsigned char* data;
	int width;
	int height;
	int channels;
};

