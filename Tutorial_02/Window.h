#pragma once
#include <glew.h>
#include <glfw3.h>

#include <iostream>
using namespace std;

#include "ShaderProgram.h"
#include "Points.h"

class Window
{
public:
	Window(int width, int height);

	~Window();

	void Input();

	void Resize();

	void Mainloop();

private:

	int m_width,m_height;
	GLFWwindow *window_ptr;

	ShaderProgram* shader;


	Points* points_renderer;
};