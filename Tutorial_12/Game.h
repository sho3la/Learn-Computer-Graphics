#pragma once
#include "Sprite.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Circle.h"

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
	//smart pointers 
	unique_ptr<Camera> cam;

	shared_ptr<Circle> circ1;
	shared_ptr<Circle> circ2;

};