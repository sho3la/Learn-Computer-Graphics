#include "Lines.h"
#include <glew.h>

Lines::Lines()
{
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
}

Lines::~Lines()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
}

void Lines::Add(glm::vec2 position)
{
	Lines_list.push_back(position);
	Update_GPU_Buffer();
}

void Lines::Delete()
{
	if(Lines_list.size() == 0) return;

	Lines_list.pop_back();
	Update_GPU_Buffer();
}

void Lines::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glDrawArrays(GL_LINES,0,(int)Lines_list.size());
}

void Lines::Update_GPU_Buffer()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,Lines_list.size() * sizeof(glm::vec2), Lines_list.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
