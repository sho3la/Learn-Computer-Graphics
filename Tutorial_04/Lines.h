#pragma once
#include <glm.hpp>
#include <vector>
using namespace std;


class Lines
{
public:
	Lines();

	~Lines();

	void Add(glm::vec2 position);

	void Delete();

	void Draw();

private:
	void Update_GPU_Buffer();

	vector<glm::vec2> Lines_list;

	//vertex array object
	unsigned int VAO;
	unsigned int VBO; // vertex buffer object
};