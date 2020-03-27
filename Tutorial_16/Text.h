#pragma once
#include "Font.h"
#include <glm.hpp>

#include <string>
#include <vector>
using namespace std;

class Text
{
public:
	Text(Font* font, glm::vec2 txt_position);

	~Text();

	void Update(string txt);

	void draw();

	glm::vec2 m_position;

private:
	Font* m_font;

	int chars_count;
	int vert_count;

	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
	unsigned int CBO; // color buffer object
	unsigned int UVBO; // uv buffer object
};