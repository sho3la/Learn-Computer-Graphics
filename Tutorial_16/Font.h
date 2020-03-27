#pragma once 
#include <glm.hpp>

struct Glyph
{
	glm::vec2 bbmin;
	glm::vec2 bbmax;
	glm::vec2 uvmin;
	glm::vec2 uvmax;
};

class Font
{
public:
	Font(const char* filename);

	~Font();

	Glyph get_glyph(char c, glm::vec2& txt_pos);

	unsigned int Atlas;
	int width, height;
	void* data;
};