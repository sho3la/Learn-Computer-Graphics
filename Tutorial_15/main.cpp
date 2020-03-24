#include <iostream>
using namespace std;

#include "Window.h"

void main()
{
	Window* window = new Window(800,600);
	window->Mainloop();
	delete window;
}