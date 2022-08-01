#include "Enemy.hpp"
#include "Hero.hpp"

#include <iostream>

void Enemy::die()
{
	isAlive = false;
	std::cout << "die";
}

void Enemy::move(sf::Time dt, CollisionMap* collisionMap)
{
	position.x = position.x + speed * cos(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
	position.y = position.y + speed * sin(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
	if (collisionMap->getCollision(position.x + 0.2, position.y + 0.5) || collisionMap->getCollision(position.x + 0.85, position.y + 0.5)
		|| collisionMap->getCollision(position.x + 0.2, position.y + 0.98) || collisionMap->getCollision(position.x + 0.85, position.y + 0.98))
	{
		position.x = position.x - speed * cos(rotation * 3.1415 / 180) * dt.asMilliseconds() / 850;
		position.y = position.y - speed * sin(rotation * 3.1415 / 180) * dt.asMilliseconds() / 850;
		srand(dt.asMicroseconds());
		setRotation(90 * (rand() % 4));
	}
	srand(dt.asMicroseconds() * position.x * position.y * speed * rotation);
	if ((rand() % 3000) < dt.asMilliseconds()) {
		setRotation(90 * (rand() % 4));
	}


	switch ((int)rotation)
	{
	case 0:
		rotationTileInc = 18;
		break;
	case 90:
		rotationTileInc = 0;
		break;
	case 180:
		rotationTileInc = 9;
		break;
	case 270:
		rotationTileInc = 27;
		break;
	default:
		break;
	}
	frameNumber = frameNumber + (float)dt.asMilliseconds() / 150;
	if (frameNumber >= 3)
		frameNumber = 0;
}
