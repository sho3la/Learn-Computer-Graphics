#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Rectangle
{
public:
	Rectangle();

	~Rectangle();

	void Draw();

	glm::mat4 GetTransformationMatrx();

	void setposition(glm::vec2 pos);

	void setscale(glm::vec2 scal);

	void setrotation(float rotation);


private:

	glm::vec2 position;
	glm::vec2 scale;
	float rotaion_angle;

	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
	unsigned int CBO; // color buffer object
};