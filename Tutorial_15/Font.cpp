#include "Font.h"
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h> 

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <glew.h>

Font::Font(const char * filename)
{
	width = 256;
	height = 256;

	unsigned char* bitmap = new unsigned char[width*height];

	// read file
	FILE* file = nullptr;
	fopen_s(&file,filename,"rb");

	// get file size
	fseek(file,0,SEEK_END);
	auto filesize = ftell(file);
	unsigned char* ttf_buffer = new unsigned char[filesize];
	rewind(file);
	fread(ttf_buffer,1,filesize,file);

	data = (void*)new stbtt_bakedchar[96];
	stbtt_BakeFontBitmap(ttf_buffer,0,32.0,bitmap,width,height,32,96,(stbtt_bakedchar*)data); // ascii code [32, 128] 96 character
	free(ttf_buffer);
	// generate texture on gpu

	glGenTextures(1,&Atlas);
	glBindTexture(GL_TEXTURE_2D, Atlas);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width,height,0,GL_RED,GL_UNSIGNED_BYTE, bitmap);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	stbi_write_png("Atlas.png",width,height,1,bitmap,0);

	free(bitmap);
}

Font::~Font()
{
	glDeleteTextures(1, &Atlas);
	free(data);
}
