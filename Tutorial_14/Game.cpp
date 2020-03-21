#include "Game.h"

#include "ShaderLibrary.h"

Game::Game()
{

	Shaders = make_unique<ShaderLibrary>();

	cam = make_unique<Camera>(0,0);

	rect1 = make_shared<Rectangle>();
	rect1->position = glm::vec2(250,250);
	rect1->scale = glm::vec2(100,100);

	circle = make_shared<Circle>(glm::vec3(400,400,50));
}

Game::~Game()
{
}

void Game::input(vector<Action> actions)
{
	for (auto action : actions)
	{
		switch (action._type)
		{
			case MOVE_UP:
			rect1->position.y -= 5;
				break;
			case MOVE_DOWN:
			rect1->position.y += 5;
				break;
			case MOVE_LEFT:
			rect1->position.x -= 5;
				break;
			case MOVE_RIGHT:
				rect1->position.x += 5;
				break;
			case SHOOT:
			{
				rect1->rotaion_angle += 1;
			}
				break;
			default:
				break;
		}
	}
}

void Game::Update_Viewport(glm::ivec2 aspectratio)
{
	cam->Update_Viewport(aspectratio.x, aspectratio.y);
}

void Game::Draw()
{
	Shaders->Colored_Shader()->use();
	Shaders->Colored_Shader()->Send_Mat4("projection", cam->Get_Projection());

	if(rect1->isCollided_SAT2(circle.get()))
	{
		Shaders->Colored_Shader()->Send_Vec4("user_color",glm::vec4(1,0,0,1));
		Shaders->Colored_Shader()->Send_Mat4("model_matrx",rect1->GetTransformationMatrx());
		rect1->Draw_Wireframe();
	
	
		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circle->gettransform());
		circle->draw_wireframe();
	}
	else
	{
		Shaders->Colored_Shader()->Send_Vec4("user_color",glm::vec4(0,1,0,1));
		Shaders->Colored_Shader()->Send_Mat4("model_matrx",rect1->GetTransformationMatrx());
		rect1->Draw();


		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circle->gettransform());
		circle->draw();
	}
}
