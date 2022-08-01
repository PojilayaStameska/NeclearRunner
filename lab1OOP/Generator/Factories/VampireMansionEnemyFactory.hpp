#pragma once
#include "IEnemyFactory.hpp"

class VampireMansionEnemyFactory :IEnemyFactory
{
public:
	VampireMansionEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize);
	virtual Enemy* createEnemy() override;
	virtual std::string factoryName() override;
};