#include "Hero.hpp"
#include <iostream>
#include <math.h>

Hero::Hero(sf::Vector2f StartPosition)
{
	this->position = StartPosition;
	this->isAlive = true;
	this->points = 0;
	this->maxHp = 6;
	this->currentHp = 6;
	this->speed = 4.2;
	hitTimeout = -1;
	isAlive = true;
	rotation = 0.0f;
	basicTile = Tile::HeroBottomFirstFrame;
	frameNumber = 0.0f;
	rotationTileInc = 0;
}

bool Hero::getAliveState()
{
	return isAlive;
}

void Hero::die()
{
	points++;
}

void Hero::move(sf::Time dt, CollisionMap* collisionMap)
{
	position.x = position.x + speed * cos(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
	position.y = position.y + speed * sin(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
	if (collisionMap->getCollision(position.x + 0.2, position.y + 0.5) || collisionMap->getCollision(position.x + 0.85, position.y + 0.5) 
		|| collisionMap->getCollision(position.x + 0.2, position.y + 0.98) || collisionMap->getCollision(position.x + 0.85, position.y + 0.98))
	{
		position.x = position.x - speed * cos(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
		position.y = position.y - speed * sin(rotation * 3.1415 / 180) * dt.asMilliseconds() / 1000;
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

void Hero::setPoints(int points)
{
	this->points = points;
}

int Hero::getPoints()
{
	return points;
}

void Hero::attack(Entity* monster)
{
	monster->takeDamage(10);
}
