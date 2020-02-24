#include "Points.h"
#include <glew.h>

Points::Points()
{
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glPointSize(5);
}

Points::~Points()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
}

void Points::Add(glm::vec2 position)
{
	points_list.push_back(position);
	Update_GPU_Buffer();
}

void Points::Delete()
{
	points_list.pop_back();
	Update_GPU_Buffer();
}

void Points::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glDrawArrays(GL_POINTS,0,points_list.size());
}

void Points::Update_GPU_Buffer()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,points_list.size() * sizeof(glm::vec2), points_list.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
