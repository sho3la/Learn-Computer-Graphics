#include "Game.h"

#include "ShaderLibrary.h"

Game::Game()
{

	Shaders = make_unique<ShaderLibrary>();

	cam = make_unique<Camera>(0,0);


	rect1 = make_shared<Rectangle>(glm::vec4(250,250,100,100));
	rect2 = make_shared<Rectangle>(glm::vec4(500,500,100,100));

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
				rect1->rotaion_angle += 0.5;
				rect2->rotaion_angle -= 0.5;
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





	if(rect1->is_Collided_SAT(rect2.get()))
	{

		Shaders->Colored_Shader()->Send_Vec4("user_color", glm::vec4(1,0,0,1));

		Shaders->Colored_Shader()->Send_Mat4("model_matrx", rect1->GetTransformationMatrx());
		rect1->Draw_Wireframe();

		Shaders->Colored_Shader()->Send_Mat4("model_matrx", rect2->GetTransformationMatrx());
		rect1->Draw_Wireframe();
	}
	else
	{
			Shaders->Colored_Shader()->Send_Vec4("user_color", glm::vec4(0,1,0,1));

	Shaders->Colored_Shader()->Send_Mat4("model_matrx", rect1->GetTransformationMatrx());
	rect1->Draw();

	Shaders->Colored_Shader()->Send_Mat4("model_matrx", rect2->GetTransformationMatrx());
	rect1->Draw();
	}


}
