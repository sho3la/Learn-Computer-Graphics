#pragma once
#include <glm.hpp>
#include <vector>
using namespace std;


class Points
{
public:
	Points();

	~Points();

	void Add(glm::vec2 position);

	void Delete();

	void Draw();

private:
	void Update_GPU_Buffer();

	vector<glm::vec2> points_list;

	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
};