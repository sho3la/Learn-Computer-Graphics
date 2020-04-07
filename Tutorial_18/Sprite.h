#pragma once
#include "Texture.h"
#include "Rectangle.h"
#include "Transform.h"
#include "Animation2D.h"


class Sprite
{
public:
	Sprite(const char * filename);

	~Sprite();

	void draw(double deltatime, AnimationType type);

	void Add_animation(const char * filename);

	Transform transformation;

private:
	Texture texture;
	Rectangle rectangle;

	vector<Animation2D*> anims;
};