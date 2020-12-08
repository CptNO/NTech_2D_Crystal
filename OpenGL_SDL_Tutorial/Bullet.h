#pragma once
#pragma once

#include <glm\glm.hpp>
#include <SpriteBatch.h>


class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime);
	~Bullet();

	void draw(NTCrystal::SpriteBatch &spriteBatch);

	//returns true when liftime of object is 0
	bool update();


private:

	//V(x,y) nv= normalizde vector nV = (x / D, Y /D) D= distance
	//velocoty is speed * direction
	int _lifetime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
};
