#include "NuclearWalker.hpp"
#include "../Utility/Rng.hpp"

#include <iostream>

NuclearWalker::NuclearWalker(Rng* rng, sf::Vector2i mapSize, sf::Vector2i position):
	mapSize(mapSize),
	position(position)
{
	this->rng = rng;
	RngDirection();
}

void NuclearWalker::RngDirection()
{
	int random = rng->getInt(4);
	switch (random)
	{
	case 0:
		dir = sf::Vector2i(0, 1);
		break;
	case 1:
		dir = sf::Vector2i(0, -1);
		break;
	case 2:
		dir = sf::Vector2i(1, 0);
		break;
	case 3:
		dir = sf::Vector2i(-1, 0);
		break;
	default: 
		dir = sf::Vector2i(0, 0);
		break;
	}
}

sf::Vector2i NuclearWalker::Walk() {
	if ((position + dir).x > 2 && (position + dir).x < mapSize.x - 2 && (position + dir).y > 2 && (position + dir).y < mapSize.y - 2)
		position += dir;
	return position;
}

sf::Vector2i NuclearWalker::getPos()
{
	return position;
}