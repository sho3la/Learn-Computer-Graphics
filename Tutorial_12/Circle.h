#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Circle
{
public:
	Circle(glm::vec3 circle);

	~Circle();

	void draw_outline();

	glm::vec2 position;
	float radius;

	glm::mat4 GetTransformationMatrx();

	bool Is_Collided(Circle* other);

private:
	int num_verts;
	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
	unsigned int CBO; // color buffer object
};