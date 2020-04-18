#include "Rectangle.h"

#include <glm.hpp>
#include <glew.h>

 RectangleSystem* RectangleSystem::_instance = nullptr;

RectangleSystem* RectangleSystem::GetInstance()
{
	if(_instance == nullptr) _instance = new RectangleSystem();

	return _instance;
}

Rectangle RectangleSystem::Generate()
{
	Rectangle result;

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

	glGenVertexArrays(1, &result.VAO);
	glGenBuffers(1, &result.VBO);
	glGenBuffers(1, &result.CBO);
	glGenBuffers(1, &result.UVBO);


	glBindVertexArray(result.VAO);

	// for vertex buffer ..
	glBindBuffer(GL_ARRAY_BUFFER, result.VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &arr[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);

	// for color buffer ..
	glBindBuffer(GL_ARRAY_BUFFER, result.CBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec4), &colors[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NULL);

	// for uv buffer ..
	glBindBuffer(GL_ARRAY_BUFFER, result.UVBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, NULL);


	glBindBuffer(GL_ARRAY_BUFFER, 0);


	return result;
}

void RectangleSystem::Delete(Rectangle & obj)
{
	glDeleteVertexArrays(1,&obj.VAO);
	glDeleteBuffers(1,&obj.VBO);
	glDeleteBuffers(1,&obj.CBO);
	glDeleteBuffers(1,&obj.UVBO);
}


RectangleSystem::RectangleSystem()
{
}