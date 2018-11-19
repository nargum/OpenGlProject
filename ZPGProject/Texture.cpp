#include "Texture.h"



Texture::Texture()
{
	textureID = SOIL_load_OGL_texture("test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}


Texture::~Texture()
{
}

void Texture::bindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
