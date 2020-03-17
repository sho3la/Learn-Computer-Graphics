#include "Game.h"

#include "ShaderLibrary.h"

Game::Game()
{

	Shaders = make_unique<ShaderLibrary>();

	cam = make_unique<Camera>(0,0);

	circ1 = make_shared<Circle>(glm::vec3(250,250,50));
	circ2 = make_shared<Circle>(glm::vec3(250,450,50));
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
			circ1->position.y -= 5;
				break;
			case MOVE_DOWN:
			circ1->position.y += 5;
				break;
			case MOVE_LEFT:
			circ1->position.x -= 5;
				break;
			case MOVE_RIGHT:
			circ1->position.x += 5;
				break;
			case SHOOT:
			{
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

	if(circ1->isCollided(circ2.get()))
	{
		Shaders->Colored_Shader()->Send_Vec4("user_color",glm::vec4(1,0,0,1));
		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circ1->gettransform());
		circ1->draw();


		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circ2->gettransform());
		circ2->draw();
	}
	else
	{
		Shaders->Colored_Shader()->Send_Vec4("user_color",glm::vec4(0,1,0,1));
		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circ1->gettransform());
		circ1->draw();


		Shaders->Colored_Shader()->Send_Mat4("model_matrx",circ2->gettransform());
		circ2->draw();
	}
}
