#include "Bullet.h"
#include <ResourceManager.h>
#include <GLTexture.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime)
{
	_position = pos;
	_direction = dir;
	_speed = speed;
	_lifetime = lifetime;
}


Bullet::~Bullet()
{
}

void Bullet::draw(NTCrystal::SpriteBatch &spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	NTCrystal::GLTexture texture = NTCrystal::ResourceManager::getTexture("Textures/PNG/Bullet.png");
	NTCrystal::Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;


	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 10, 10);
	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);


}

bool Bullet::update()
{
	_position += _direction * _speed;
	_lifetime--;
	if (_lifetime == 0)
	{
		return true;
	}
	return false;
}

