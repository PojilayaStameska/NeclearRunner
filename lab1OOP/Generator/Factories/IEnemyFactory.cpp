#include "IEnemyFactory.hpp"
#include <iostream>

sf::Vector2f IEnemyFactory::randomEnemyPos()
{
	bool isInvalidPosition = true;
	while (isInvalidPosition)
	{
		int xCord = randomiser.getInt(0, mapSize.x - 1);
		int yCord = randomiser.getInt(0, mapSize.y - 1);
		if (colMap->getCollision(xCord, yCord) == false && map->getTile(xCord, yCord) != Tile::Unused)
		{
			return sf::Vector2f(xCord, yCord);
		}
	}
}