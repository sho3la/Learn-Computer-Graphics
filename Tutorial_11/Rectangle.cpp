#include "Rectangle.h"

#include <glew.h>

Rectangle::Rectangle() : 
	position(glm::vec2(0)),
	scale(glm::vec2(1)),
	rotaion_angle(0.0f)
{
	glm::vec2 arr[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glm::vec4 colors[6] = {
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1)
	};

	glm::vec2 uv[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&CBO);
	glGenBuffers(1,&UVBO);



	glBindVertexArray(VAO);
	
	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &arr[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,CBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,4,GL_FLOAT,false,0,NULL);

	// for uv buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,UVBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,false,0,NULL);


	glBindBuffer(GL_ARRAY_BUFFER,0);

}

Rectangle::Rectangle(glm::vec4 rect) : rotaion_angle(0)
{
	position = glm::vec2(rect.x,rect.y);
	scale = glm::vec2(rect.z,rect.w);

		glm::vec2 arr[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glm::vec4 colors[6] = {
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1),
		glm::vec4(1,1,1,1)
	};

	glm::vec2 uv[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),
		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)
	};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&CBO);
	glGenBuffers(1,&UVBO);



	glBindVertexArray(VAO);
	
	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &arr[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,0,NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,CBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,4,GL_FLOAT,false,0,NULL);

	// for uv buffer ..
	glBindBuffer(GL_ARRAY_BUFFER,UVBO);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,false,0,NULL);


	glBindBuffer(GL_ARRAY_BUFFER,0);
}

Rectangle::~Rectangle()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&CBO);
	glDeleteBuffers(1,&UVBO);

}

void Rectangle::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,6);
}

void Rectangle::Draw_Wireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,6);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

glm::mat4 Rectangle::GetTransformationMatrx()
{
	glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f),glm::vec3(position,1.0f));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f),rotaion_angle,glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f),glm::vec3(scale,1.0f));

	return tarnslation * scal * Rotation ;
}


////////////// AABB axis aligned bounding box

bool Rectangle::is_Collided(Rectangle * other)
{

	if(position.x < other->position.x + other->scale.x &&
		position.x + scale.x > other->position.x &&
		position.y < other->position.y + other->scale.y &&
		position.y + scale.y > other->position.y)
	{
		//collision detected
		return true;
	}

	return false;
}
