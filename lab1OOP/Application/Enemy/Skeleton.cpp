#include "Skeleton.hpp"


Skeleton::Skeleton(int hp, sf::Vector2f pos, float spd)
{
	this->maxHp = hp;
	this->currentHp = hp;
	this->position = pos;
	this->speed = spd;
	isAlive = false;
	rotation = 0.0f;
	basicTile = Tile::SkeletonBottomFirstFrame;
	frameNumber = 0.0f;
	rotationTileInc = 0;
}

void Skeleton::attack(Entity* hero)
{
	if (hero->getHitTimeout() < 1)
	{
		hero->takeDamage(1);
	}
}