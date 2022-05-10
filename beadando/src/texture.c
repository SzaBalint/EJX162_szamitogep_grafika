#include <SOIL/SOIL.h>

#include "texture.h"


GLuint load_texture(char* filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint texture_name;
	Pixel* image;
	glGenTextures(1, &texture_name);

	int width;
	int height;

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA); // @suppress("Symbol is not resolved")

	glBindTexture(GL_TEXTURE_2D, texture_name);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	return texture_name;
}
