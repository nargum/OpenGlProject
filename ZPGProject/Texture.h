#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>

using namespace std;

class Texture
{
public:
	Texture(string path);
	~Texture();
	void bindTexture();

private:
	GLuint textureID;
	string path;
	unsigned char* data;
	int width;
	int height;
	int channels;
};

