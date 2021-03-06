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

	window_ptr = glfwCreateWindow(width, height, "Tutorial 19",NULL,NULL);
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

	auto rect_sys = RectangleSystem::GetInstance();
	rect = rect_sys->Generate();
}

Window::~Window()
{
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
	}
	else if (glfwGetKey(window_ptr, GLFW_KEY_LEFT))
	{
	}
	else
	{
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
		Shaders->Checkboard_Shader()->use();
		Shaders->Checkboard_Shader()->Send_Mat4("projection", camera->Get_Projection());
		Shaders->Checkboard_Shader()->Send_Mat4("model_matrx", glm::scale(glm::mat4(1), glm::vec3(m_width,m_height,1)));
		Shaders->Checkboard_Shader()->Send_vec2("resolution", glm::vec2(m_width,m_height));
		rect.draw();
			
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();

		endtime = glfwGetTime();
		delta = endtime - starttime;
	}
}
