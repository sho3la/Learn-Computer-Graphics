#include "Sprite.h"

Sprite::Sprite(const char * filename)
{
	auto tex_sys = TextureSystem::GetInstance();
	texture = tex_sys->Generate(filename);

	auto rect_sys = RectangleSystem::GetInstance();
	rectangle = rect_sys->Generate();
}

Sprite::~Sprite()
{
	auto tex_sys = TextureSystem::GetInstance();
	tex_sys->Delete(texture);

	auto rect_sys = RectangleSystem::GetInstance();
	rect_sys->Delete(rectangle);


	for(auto& o : anims)
		delete o;
}

void Sprite::draw(double deltatime, AnimationType type)
{

	if(anims[type])
	{
		anims[type]->play(texture,rectangle,deltatime);
	}

	texture.use();
	rectangle.draw();
}

void Sprite::Add_animation(const char * filename)
{
	auto anim = new Animation2D(filename);

	anims.push_back(anim);
}
