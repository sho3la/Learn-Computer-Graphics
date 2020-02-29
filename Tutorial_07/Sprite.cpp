#include "Sprite.h"

Sprite::Sprite(const char * imagepath, glm::vec2 position)
{
	texture = new Texture(imagepath);
	rectangle = new Rectangle();
	rectangle->setposition(position);
	rectangle->setscale(glm::vec2(100));

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

glm::mat4 Sprite::transformation()
{
	return rectangle->GetTransformationMatrx();
}

void Sprite::move_up(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.y -= 1 * speed;
	rectangle->setposition(pos);
}

void Sprite::move_down(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.y += 1 * speed;
	rectangle->setposition(pos);
}

void Sprite::move_left(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.x -= 1 * speed;
	rectangle->setposition(pos);
}

void Sprite::move_right(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.x += 1 * speed;
	rectangle->setposition(pos);
}
