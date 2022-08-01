#include "Slime.hpp"


Slime::Slime(int hp, sf::Vector2f pos, float spd)
{
	this->maxHp = hp;
	this->currentHp = hp;
	this->position = pos;
	this->speed = spd;
	isAlive = false;
	rotation = 0.0f;
	basicTile = Tile::SlimeBottomFirstFrame;
	frameNumber = 0.0f;
	rotationTileInc = 0;
}

void Slime::attack(Entity* hero)
{
	if (hero->getHitTimeout() < 1)
	{
		hero->setCurTile(basicTile);
		hero->takeDamage(1);
	}
}