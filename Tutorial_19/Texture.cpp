#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glew.h>
#include <iostream>
using namespace std;

TextureSystem* TextureSystem::_instance = nullptr;

TextureSystem * TextureSystem::GetInstance()
{
	if(_instance == nullptr) _instance = new TextureSystem();

	return _instance;
}

Texture TextureSystem::Generate(const char * filename)
{
	Texture result;

	int width, height, numcomponents;
	unsigned char* data;
	unsigned int textureID;

	glGenTextures(1, &textureID);

	data = stbi_load(filename, &width, &height, &numcomponents, STBI_rgb_alpha);

	result.width = width;
	result.height = height;
	result.ID = textureID;

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// ********* texture minimize & maxmize operation
		// to solve pixlation problem
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_NEAREST
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		cout << "failed to load image : " << filename << endl;
		cout << "============================================" << endl;
		stbi_image_free(data);
	}

	stbi_image_free(data);

	return result;
}

void TextureSystem::Delete(Texture& obj)
{
	glDeleteTextures(1,&obj.ID);
}

TextureSystem::TextureSystem()
{

}
