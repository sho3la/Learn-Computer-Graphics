#pragma once

// singlton pattern 

struct Rectangle
{
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int CBO;  // color buffer object
	unsigned int UVBO; // uv buffer object
};

class RectangleSystem
{
public:
	static RectangleSystem* GetInstance();

	Rectangle Generate();

	void Delete(Rectangle& obj);
	
private:
	RectangleSystem();

	static RectangleSystem* _instance;
};