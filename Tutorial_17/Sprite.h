#pragma once
#include "Rectangle.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite(const char* imagepath, glm::vec2 position);

	~Sprite();

	void draw();

	glm::mat4 transformation();

	void move_up   (float speed);
	void move_down (float speed);
	void move_left (float speed);
	void move_right(float speed);

	void scale(glm::vec2 _scale);
	glm::vec2 getposition();


private:
	Texture* texture;
	Rectangle* rectangle;
};