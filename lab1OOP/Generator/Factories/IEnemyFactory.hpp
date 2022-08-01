#pragma once
#include "../../Application/Enemy.hpp"
#include "../../Utility/Rng.hpp"
#include "../../Map/Map.hpp"
class IEnemyFactory
{
public:
	virtual Enemy* createEnemy() = 0;
	virtual std::string factoryName() = 0;

protected:
	sf::Vector2f randomEnemyPos();

	Rng randomiser;
	CollisionMap* colMap;
	Map* map;
	sf::Vector2i mapSize;
};