#pragma once 

class Font
{
public:
	Font(const char* filename);

	~Font();

	unsigned int Atlas;
	int width, height;
	void* data;
};