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

	window_ptr = glfwCreateWindow(width, height, "Tutorial_04",NULL,NULL);
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

			uniform mat4 projection;
			uniform mat4 model_matrx;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, 0.0, 1.0);
			};
)CODE";
	
	const char* fs = R"CODE(

			#version 330 core
			out vec4 finalcolor;
			void main()
			{
				finalcolor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
			};
)CODE";


	camera = new Camera(m_width,m_height);
	shader = new ShaderProgram(vs,fs);

	points_renderer = new Points();
	points_renderer->Add(glm::vec2(10,10));
	points_renderer->Add(glm::vec2(50,50));
	points_renderer->Add(glm::vec2(155,155));

	lines_renderer = new Lines();


	triangle_renderer = new Triangle();
	triangle_renderer->setposition(glm::vec2(200,250));
	triangle_renderer->setscale(glm::vec2(100,100));
}

Window::~Window()
{
	delete points_renderer;
	delete shader;
	delete camera;
	delete lines_renderer;
	delete triangle_renderer;
	glfwTerminate();
}

static glm::vec2 pos = glm::vec2(200,250);
void Window::Input()
{
	if(glfwGetKey(window_ptr,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window_ptr,true);
	}


	if(glfwGetKey(window_ptr,GLFW_KEY_DELETE))
	{
		points_renderer->Delete();
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_UP))
	{
		pos.y -= 1;
		triangle_renderer->setposition(pos);
	}
	
	if(glfwGetKey(window_ptr,GLFW_KEY_DOWN))
	{
		pos.y += 1;
		triangle_renderer->setposition(pos);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_LEFT))
	{
		pos.x -= 1;
		triangle_renderer->setposition(pos);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_RIGHT))
	{
		pos.x += 1;
		triangle_renderer->setposition(pos);
	}

	//left click = 0
	//right = 1
	// middle = 2
	if(glfwGetMouseButton(window_ptr,0))
	{
		double x , y;
		glfwGetCursorPos(window_ptr,&x,&y);
		glm::vec2 mouse_position(x,y);
		lines_renderer->Add(mouse_position);
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

float angle = 0;
void Window::Mainloop()
{
	while (!glfwWindowShouldClose(window_ptr))
	{
		//for each frame 
		Resize();
		Input();

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		angle += 0.01f;
		triangle_renderer->setrotation(angle);

		// all drawing goes here ..
		shader->use();
		shader->Send_Mat4("projection", camera->Get_Projection());
		shader->Send_Mat4("model_matrx", triangle_renderer->GetTransformationMatrx());
		//points_renderer->Draw();
		//lines_renderer->Draw();
		triangle_renderer->Draw();

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
}
