#include "Spider.hpp"


Spider::Spider(int hp, sf::Vector2f pos, float spd)
{
	this->maxHp = hp;
	this->currentHp = hp;
	this->position = pos;
	this->speed = spd;
	isAlive = false;
	rotation = 0.0f;
	basicTile = Tile::SpiderBottomFirstFrame;
	frameNumber = 0.0f;
	rotationTileInc = 0;
}


void Spider::attack(Entity* hero)
{
	if (hero->getHitTimeout() < 1)
	{
		hero->setSpeed(hero->Speed() - 0.5);
		hero->takeDamage(1);
	}

}