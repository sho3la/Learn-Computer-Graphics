#pragma once

class Texture
{
public:
	Texture(const char* filepath);

	~Texture();

	void use();

private:
	int width, height, numcomponents;
	unsigned char* data;
	unsigned int textureID;
};