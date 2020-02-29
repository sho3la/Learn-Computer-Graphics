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

	window_ptr = glfwCreateWindow(width, height, "Tutorial_08",NULL,NULL);
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


	const char* vs = R"CODE(
			#version 330 core
			layout(location = 0) in vec2 point;
			layout(location = 1) in vec4 color;
			layout(location = 2) in vec2 uv;

			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;
			out vec2 vertex_uv;

			void main()
			{
				gl_Position = projection * model_matrx * vec4(point.x, point.y, 0.0, 1.0);
				vertex_color = color;
				vertex_uv = uv;
			};
)CODE";
	
	const char* fs = R"CODE(

			#version 330 core
			out vec4 finalcolor;

			in vec4 vertex_color;
			in vec2 vertex_uv;

			uniform sampler2D sprite;

			void main()
			{
				finalcolor = vertex_color * texture(sprite,vertex_uv);
			};
)CODE";


	camera = new Camera(m_width,m_height);
	shader = new ShaderProgram(vs,fs);

	spaceship = nullptr;
	openfile_button = new Sprite("D:\\OpenglTutorial\\Learn-Computer-Graphics\\resources\\button.png",glm::vec2(0));
	openfile_button->scale(glm::vec2(50.0f));
}

Window::~Window()
{
	delete shader;
	delete camera;
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
		spaceship->move_up(5);
	}
	
	if(glfwGetKey(window_ptr,GLFW_KEY_DOWN))
	{
		spaceship->move_down(5);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_LEFT))
	{
		spaceship->move_left(5);
	}

	if(glfwGetKey(window_ptr,GLFW_KEY_RIGHT))
	{
		spaceship->move_right(5);
	}

	//left click = 0
	//right = 1
	// middle = 2
	if(glfwGetMouseButton(window_ptr,0))
	{
		double x , y;
		glfwGetCursorPos(window_ptr,&x,&y);
		glm::vec2 mouse_position(x,y);

		if(mouse_position.x > 50 || mouse_position.y > 50) return;

		auto path = FileDialog::Open();
		if(spaceship) delete spaceship;
		spaceship = new Sprite(path,glm::vec2(100,100));
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// all drawing goes here ..
		shader->use();
		shader->Send_Mat4("projection", camera->Get_Projection());

		shader->Send_Mat4("model_matrx", openfile_button->transformation());
		openfile_button->draw();

		if(spaceship)
		{
			shader->Send_Mat4("model_matrx", spaceship->transformation());
			spaceship->draw();
		}

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
	}
}
