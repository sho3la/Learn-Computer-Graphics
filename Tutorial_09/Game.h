#pragma once
#include "Sprite.h"
#include "ShaderProgram.h"

class Game
{
public:
	Game();

	~Game();

	void input();

	void Draw(ShaderProgram* shader);

private:
	Sprite* background;
	Sprite* sun;
	Sprite* planet;
	Sprite* planet_mask;
	Sprite* planet2;
	Sprite* spaceship;
};