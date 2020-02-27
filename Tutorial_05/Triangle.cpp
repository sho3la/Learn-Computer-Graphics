#include "Triangle.h"

#include <glew.h>

Triangle::Triangle() : 
	position(glm::vec2(0)),
	scale(glm::vec2(1)),
	rotaion_angle(0.0f)
{
	glm::vec2 arr[3] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0)
	};

	glm::vec4 colors[3] = {
		glm::vec4(1,0,0,1),
		glm::vec4(0,1,0,1),
		glm::vec4(0,0,1,1)
	};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&CBO);


	glBindVertexArray(VAO);
	
	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,3 * sizeof(glm::vec2), &arr[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,CBO);
	glBufferData(GL_ARRAY_BUFFER,3 * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,4,GL_FLOAT,false,0,NULL);


	glBindBuffer(GL_ARRAY_BUFFER,0);

}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&CBO);
}

void Triangle::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,3);
}

glm::mat4 Triangle::GetTransformationMatrx()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f),glm::vec3(position,1.0f));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f),rotaion_angle,glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f),glm::vec3(scale,1.0f));

	return tarnslation * scal * Rotation ;
}

void Triangle::setposition(glm::vec2 pos)
{
	position = pos;
}

void Triangle::setscale(glm::vec2 scal)
{
	scale = scal;
}

void Triangle::setrotation(float rotation)
{
	rotaion_angle = rotation;
}
