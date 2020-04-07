#pragma once
#include <glew.h>
#include <glfw3.h>

#include <iostream>
using namespace std;


#include "ShaderLibrary.h"
#include "Camera.h"

#include "Player.h"


class Window
{
public:
	Window(int width, int height);

	~Window();

	void Input();

	void Resize();

	void Mainloop();

	Player* player;

private:
	int m_width,m_height;
	GLFWwindow *window_ptr;
	double starttime, endtime, delta;
};