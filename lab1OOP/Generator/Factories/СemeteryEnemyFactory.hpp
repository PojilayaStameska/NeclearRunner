#pragma once
#include "IEnemyFactory.hpp"

class CemeteryEnemyFactory :IEnemyFactory
{
public:
	CemeteryEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize);
	virtual Enemy* createEnemy() override;
	virtual std::string factoryName() override;
};