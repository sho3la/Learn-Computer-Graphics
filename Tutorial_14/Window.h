#pragma once
#include <glew.h>
#include <glfw3.h>

#include <iostream>
using namespace std;

#include "Game.h"

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

	Game* game;

	vector<Action> actions;
	static int key_state;
};