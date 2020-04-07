#include "Window.h"

Window::Window(int width, int height)
	:m_width(width),
	m_height(height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED,true);

	window_ptr = glfwCreateWindow(width, height, "Tutorial 18",NULL,NULL);
	if(window_ptr ==  nullptr)
	{
		cout<<"erorr initilize glfw"<<endl;
		return;
	}

	glfwMakeContextCurrent(window_ptr);

	if(glewInit())
	{
		cout<<"erorr initilize glew"<<endl;
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	starttime = 0;
	endtime = 0;
	delta = 0;

	Shaders = make_unique<ShaderLibrary>();
	camera = make_unique<Camera>(0,0);

	//sp = new Sprite("resources/spaceship.png");

	player = new Player();
}

Window::~Window()
{
	delete player;
	glfwTerminate();
}

void Window::Input()
{
	if(glfwGetKey(window_ptr,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window_ptr,true);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_RIGHT))
	{
		player->move_right();
	}
	else if (glfwGetKey(window_ptr, GLFW_KEY_LEFT))
	{
		player->move_left();
	}
	else
	{
		player->stop();
	}

}

void Window::Resize()
{
	int width,height;
	glfwGetWindowSize(window_ptr,&width,&height);
	if(width != m_width || height != m_height)
	{
		m_width = width;
		m_height = height;
		glViewport(0,0,width,height);
		camera->Update_Viewport(width,height);
		printf("resized \n");
	}
}

void Window::Mainloop()
{
	while (!glfwWindowShouldClose(window_ptr))
	{
		starttime =  glfwGetTime();

		//for each frame 
		Resize();
		Input();

		glClearColor(0.39f,0.58f,0.92f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// all drawing goes here ..
		Shaders->Textured_Shader()->use();
		Shaders->Textured_Shader()->Send_Mat4("projection", camera->Get_Projection());

		Shaders->Textured_Shader()->Send_Mat4("model_matrx", player->Transformation());
		player->draw(delta);
			
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();

		endtime = glfwGetTime();
		delta = endtime - starttime;
	}
}
