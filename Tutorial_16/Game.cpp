#include "Game.h"

#include "ShaderLibrary.h"

Game::Game()
{

	Shaders = make_unique<ShaderLibrary>();

	cam = make_unique<Camera>(0,0);


	background = new Sprite("resources/bg.png",glm::vec2(0));
	background->scale(glm::vec2(2000,2000));

	sun = new Sprite("resources/sun.png",glm::vec2(-50,500));
	sun->scale(glm::vec2(400));

	planet = new Sprite("resources/planet.png", glm::vec2(1200,250));
	planet->scale(glm::vec2(200));

	planet_mask = new Sprite("resources/Mask Right 1.png", glm::vec2(1200,250));
	planet_mask->scale(glm::vec2(201));


	planet2 = new Sprite("resources/planet2.png", glm::vec2(1500,500));
	planet2->scale(glm::vec2(600));

	spaceship = new Sprite("resources/spaceship.png", glm::vec2(700,500));
	spaceship->scale(glm::vec2(100));

	font = make_shared<Font>("resources/fonts/airstrike.ttf");
	score_text = make_shared<Text>(font.get(), glm::vec2(20,30));
	score_text->Update("score");
	score_value = 0;
}

Game::~Game()
{
	delete background;
	delete sun;
	delete planet;
	delete planet_mask;
	delete planet2;
	delete spaceship;
}

void Game::input(vector<Action> actions)
{
	for (auto action : actions)
	{
		switch (action._type)
		{
			case MOVE_UP:
				spaceship->move_up(5);
				break;
			case MOVE_DOWN:
				spaceship->move_down(5);
				break;
			case MOVE_LEFT:
				spaceship->move_left(5);
				break;
			case MOVE_RIGHT:
				spaceship->move_right(5);
				break;
			case SHOOT: // space pressed
			{
				score_value += 100;
				string res = "score " + std::to_string(score_value);
				score_text->Update(res);
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
	Shaders->Textured_Shader()->use();
	Shaders->Textured_Shader()->Send_Mat4("projection", cam->Get_Projection());


	Shaders->Textured_Shader()->Send_Mat4("model_matrx", background->transformation());
	background->draw();

	Shaders->Textured_Shader()->Send_Mat4("model_matrx", sun->transformation());
	sun->draw();

	Shaders->Textured_Shader()->Send_Mat4("model_matrx", planet->transformation());
	planet->draw();

	Shaders->Textured_Shader()->Send_Mat4("model_matrx", planet_mask->transformation());
	planet_mask->draw();

	Shaders->Textured_Shader()->Send_Mat4("model_matrx", planet2->transformation());
	planet2->draw();


	Shaders->Textured_Shader()->Send_Mat4("model_matrx", spaceship->transformation());
	spaceship->draw();


	Shaders->Font_Shader()->use();
	Shaders->Font_Shader()->Send_Mat4("projection", cam->Get_Projection());
	//Shaders->Font_Shader()->Send_Vec4("user_color", glm::vec4(1,0,1,1));
	score_text->draw();
}
