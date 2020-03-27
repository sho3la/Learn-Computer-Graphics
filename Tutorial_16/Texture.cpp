#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glew.h>
#include <iostream>
using namespace std;

Texture::Texture(const char * filepath)
{
	glGenTextures(1,&textureID);

	data = stbi_load(filepath, &width, &height, &numcomponents, STBI_rgb_alpha);

	if(data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else
	{
		cout << "failed to load image : "<< filepath <<endl;
		cout << "============================================"<<endl;
		stbi_image_free(data);
	}
}

Texture::~Texture()
{
	stbi_image_free(data);
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

int Texture::getwidth()
{
	return width;
}

int Texture::getheight()
{
	return height;
}

unsigned char * Texture::getdata()
{
	return data;
}
