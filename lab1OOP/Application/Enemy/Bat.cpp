#include "Bat.hpp"


Bat::Bat(int hp, sf::Vector2f pos, float spd)
{
	this->maxHp = hp;
	this->currentHp = hp;
	this->position = pos;
	this->speed = spd;
	isAlive = false;
	rotation = 0.0f;
	basicTile = Tile::BatBottomFirstFrame;
	frameNumber = 0.0f;
	rotationTileInc = 0;
}

void Bat::attack(Entity* hero)
{
	if (hero->getHitTimeout() < 1)
	{
		hero->setSpeed(hero->Speed() + 0.5);
		hero->takeDamage(0);
	}
}