#include "Texture.h"



Texture::Texture(string path)
{
	this->path = path;
	const char* p = path.c_str();
	glGenTextures(1, &textureID);
	data = SOIL_load_image(p, &width, &height, &channels, 0);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
	
}


Texture::~Texture()
{
}

void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
