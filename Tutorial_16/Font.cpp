#include "Font.h"
#include <stdio.h>
#include <stdlib.h>

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


	free(bitmap);
}

Font::~Font()
{
	glDeleteTextures(1, &Atlas);
	free(data);
}

Glyph Font::get_glyph(char c, glm::vec2 & txt_pos)
{
	Glyph glyph;

	// characters in range [32 --- 128] ascii check
	if(c >= 32 && c < 128)
	{
		stbtt_aligned_quad q;
		stbtt_GetBakedQuad((stbtt_bakedchar*)data, width,height, c - 32 , &txt_pos.x , &txt_pos.y,&q,1);

		glyph.bbmin = glm::vec2(q.x0,q.y0); // bounding box
		glyph.bbmax = glm::vec2(q.x1,q.y1);

		glyph.uvmin = glm::vec2(q.s0,q.t0); // uvs
		glyph.uvmax = glm::vec2(q.s1,q.t1);

	}
	return glyph;
}
