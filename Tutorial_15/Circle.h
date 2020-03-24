#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>
using namespace std;



class Circle
{

public:
	Circle(glm::vec3 circ);

	~Circle();

	void draw();
	void draw_wireframe();

	glm::mat4 gettransform();

	bool isCollided(Circle* other);

	float radius;
	glm::vec2 position;

private:
	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
	unsigned int CBO; // color buffer object

	int num_verts;
};