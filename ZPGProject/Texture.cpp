#include "Texture.h"



Texture::Texture()
{
	//glGenTextures(1, &textureID);
	//data = SOIL_load_image("../textures/Brick_Block.png", &width, &height, &channels, 0);
}


Texture::~Texture()
{
}

void Texture::bindTexture()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = SOIL_load_image("../textures/wall.jpg", &width, &height, &channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	SOIL_free_image_data(data);
	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, // Type of texture 1D, 2D, 3D
		0, // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB, // Internal colour format to convert to
		1024, // Image width i.e. 640
		1024, // Image height i.e. 480
		0, // Border width in pixels (can either be 1 or 0)
		GL_BGR, // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_INT, // Image data type
		&textureID);
	glGenerateMipmap(GL_TEXTURE_2D);*/
}
