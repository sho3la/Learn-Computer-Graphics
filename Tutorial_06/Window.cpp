#include "Window.h"

Window::Window(int width, int height)
	:m_width(width),
	m_height(height)
{
	glfwInit();

	// opengl 3.3 modern opengl 1.0 ==== 4.5
	// vulkan
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ptr = glfwCreateWindow(width, height, "Tutorial_06",NULL,NULL);
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


	const char* vs = R"CODE(
			#version 330 core
			layout(location = 0) in vec2 point;
			layout(location = 1) in vec4 color;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, 0.0, 1.0);
				vertex_color = color;
			};
)CODE";
	
	const char* fs = R"CODE(

			#version 330 core
			out vec4 finalcolor;

			in vec4 vertex_color;

			void main()
			{
				finalcolor = vertex_color;
			};
)CODE";


	camera = new Camera(m_width,m_height);
	shader = new ShaderProgram(vs,fs);

	rect = new Rectangle();
	rect->setposition(glm::vec2(200,250));
	rect->setscale(glm::vec2(100,100));
}

Window::~Window()
{
	delete shader;
	delete camera;
	delete rect;
	glfwTerminate();
}

static glm::vec2 pos = glm::vec2(200,250);
void Window::Input()
{
	if(glfwGetKey(window_ptr,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window_ptr,true);
	}


	if(glfwGetKey(window_ptr,GLFW_KEY_UP))
	{
		pos.y -= 1;
		rect->setposition(pos);
	}
	
	if(glfwGetKey(window_ptr,GLFW_KEY_DOWN))
	{
		pos.y += 1;
		rect->setposition(pos);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_LEFT))
	{
		pos.x -= 1;
		rect->setposition(pos);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_RIGHT))
	{
		pos.x += 1;
		rect->setposition(pos);
	}

	//left click = 0
	//right = 1
	// middle = 2
	if(glfwGetMouseButton(window_ptr,0))
	{
		double x , y;
		glfwGetCursorPos(window_ptr,&x,&y);
		glm::vec2 mouse_position(x,y);
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
		camera->Update_Viewport(m_width,m_height);
		printf("resized \n");
	}
}

void Window::Mainloop()
{
	while (!glfwWindowShouldClose(window_ptr))
	{
		//for each frame 
		Resize();
		Input();

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// all drawing goes here ..
		shader->use();
		shader->Send_Mat4("projection", camera->Get_Projection());
		shader->Send_Mat4("model_matrx", rect->GetTransformationMatrx());

		rect->Draw();

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
}
