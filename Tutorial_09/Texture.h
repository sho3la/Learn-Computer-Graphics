#pragma once

class Texture
{
public:
	Texture(const char* filepath);

	~Texture();

	void use();

	int getwidth();

	int getheight();

	unsigned char* getdata();

private:
	int width, height, numcomponents;
	unsigned char* data;
	unsigned int textureID;
};