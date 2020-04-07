#pragma once
#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include <vector>
using namespace std;


enum Type
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	SHOOT
};

struct Action
{
	Type _type;
	std::pair<bool,char> iskey_pressed;
	glm::vec2 mouse_pos;
};


class Game
{
public:
	Game();

	~Game();

	void input(vector<Action> actions);

	void Update_Viewport(glm::ivec2 aspectratio);

	void Draw();

private:

	unique_ptr<Camera> cam;

	Sprite* background;
	Sprite* sun;
	Sprite* planet;
	Sprite* planet_mask;
	Sprite* planet2;
	Sprite* spaceship;
	Sprite* enemy;

	Texture* bullet;
	vector<Rectangle*> bullets;
};