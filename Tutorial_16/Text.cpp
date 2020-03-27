#include "Text.h"

#include <glew.h>


Text::Text(Font * font, glm::vec2 txt_position)
	: m_font(font),
	m_position(txt_position)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &CBO);
	glGenBuffers(1, &UVBO);
}

Text::~Text()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &CBO);
	glDeleteBuffers(1, &UVBO);
}

void Text::Update(string txt)
{
	vector<glm::vec2> verts;
	vector<glm::vec4> colors;
	vector<glm::vec2> uvs;

	glm::vec2 tmp_pos = m_position;

	for(auto& character : txt)
	{
		auto glyph = m_font->get_glyph(character, tmp_pos);

		// rectangle verts ..
		// first tringle
		verts.push_back(glyph.bbmin);
		verts.push_back(glm::vec2(glyph.bbmax.x , glyph.bbmin.y));
		verts.push_back(glyph.bbmax);

		// second tringle
		verts.push_back(glyph.bbmin);
		verts.push_back(glyph.bbmax);
		verts.push_back(glm::vec2(glyph.bbmin.x, glyph.bbmax.y));

		// rectangle uvs ..
		// first tringle
		uvs.push_back(glyph.uvmin);
		uvs.push_back(glm::vec2(glyph.uvmax.x, glyph.uvmin.y));
		uvs.push_back(glyph.uvmax);
		// second tringle
		uvs.push_back(glyph.uvmin);
		uvs.push_back(glyph.uvmax);
		uvs.push_back(glm::vec2(glyph.uvmin.x, glyph.uvmax.y));


		// rectangle colors ..
		// first tringle
		colors.push_back(glm::vec4(1));
		colors.push_back(glm::vec4(1,0,0,0));
		colors.push_back(glm::vec4(1,0,1,0));
		// second tringle
		colors.push_back(glm::vec4(1,0,1,0));
		colors.push_back(glm::vec4(1));
		colors.push_back(glm::vec4(1,0,0,0));
	}

	vert_count = (int)verts.size();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,verts.size() * sizeof(glm::vec2), verts.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);


	glBindBuffer(GL_ARRAY_BUFFER,CBO);
	glBufferData(GL_ARRAY_BUFFER,colors.size() * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Text::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_font->Atlas);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vert_count);
}
