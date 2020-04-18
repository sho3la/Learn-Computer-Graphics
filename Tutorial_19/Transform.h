#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

struct Transform
{
	glm::vec2 position = glm::vec2(0);
	glm::vec2 scale = glm::vec2(1);
	float angle = 0;

	glm::mat4 Get()
	{
		glm::mat4 tarnslation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));
		glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

		return tarnslation * scal * Rotation;
	}
};