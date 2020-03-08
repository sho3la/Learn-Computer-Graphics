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


	enemy = new Sprite("resources/spaceship.png", glm::vec2(700,200));
	enemy->scale(glm::vec2(50));

	bullet = new Texture("resources/bullet.png");
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
			case SHOOT:
			{
				//generate rectangles as bullets
				Rectangle* rect = new Rectangle();
				glm::vec2 pos = spaceship->getposition();
				pos += 40;
				rect->setposition(pos);
				rect->setscale(glm::vec2(20,40));
				bullets.push_back(rect);
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


	Shaders->Colored_Shader()->use();
	Shaders->Colored_Shader()->Send_Mat4("projection", cam->Get_Projection());
	Shaders->Colored_Shader()->Send_Mat4("model_matrx", enemy->transformation());
	enemy->draw_wireframe();

	/*bullet->use();
	for(size_t i =0; i < bullets.size(); ++i)
	{
		auto tmp = bullets[i]->getposition();
		if(tmp.y < -10)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			continue;
		}

		tmp.y -= 10;
		bullets[i]->setposition(tmp);


		Shaders->Textured_Shader()->Send_Mat4("model_matrx", bullets[i]->GetTransformationMatrx());
		bullets[i]->Draw();
	}*/




	for(size_t i =0; i < bullets.size(); ++i)
	{
		auto tmp = bullets[i]->getposition();
		if(tmp.y < -10)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			continue;
		}

		tmp.y -= 10;
		bullets[i]->setposition(tmp);


		Shaders->Colored_Shader()->Send_Mat4("model_matrx", bullets[i]->GetTransformationMatrx());
		bullets[i]->Draw();
	}
}
