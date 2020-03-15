#include "Sprite.h"

Sprite::Sprite(const char * imagepath, glm::vec2 position)
{
	texture = new Texture(imagepath);
	rectangle = new Rectangle();
	rectangle->position = position;
	rectangle->scale = glm::vec2(100);

}

Sprite::~Sprite()
{
	delete texture;
	delete rectangle;
}

void Sprite::draw()
{
	texture->use();
	rectangle->Draw();
}

void Sprite::draw_wireframe()
{
	rectangle->Draw_Wireframe();
}

glm::mat4 Sprite::transformation()
{
	return rectangle->GetTransformationMatrx();
}

void Sprite::move_up(float speed)
{
	rectangle->position.y -= speed;
}

void Sprite::move_down(float speed)
{
	rectangle->position.y += speed;
}

void Sprite::move_left(float speed)
{
	rectangle->position.x -= speed;
}

void Sprite::move_right(float speed)
{
	rectangle->position.x += speed;
}

