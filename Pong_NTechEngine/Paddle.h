#pragma once
#include "Entity.h"
#include <glm\glm.hpp>
#include <vector>
#include <SpriteBatch.h>



class Paddle : public Entity
{
public:
	Paddle();
	~Paddle();

	virtual void update(float deltaTime) override;

private:

};
