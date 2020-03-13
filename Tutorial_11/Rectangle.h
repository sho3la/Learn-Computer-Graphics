#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Rectangle
{
public:
	Rectangle();
	Rectangle(glm::vec4 rect);

	~Rectangle();

	void Draw();

	void Draw_Wireframe();

	glm::mat4 GetTransformationMatrx();

	bool is_Collided(Rectangle* other);


	glm::vec2 position;
	glm::vec2 scale;
	float rotaion_angle;

private:

	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
	unsigned int CBO; // color buffer object
	unsigned int UVBO; // uv buffer object
};