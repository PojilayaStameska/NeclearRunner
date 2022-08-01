#include "ÑemeteryEnemyFactory.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Skeleton.hpp"
#include "../../Application/Enemy/Bat.hpp"

CemeteryEnemyFactory::CemeteryEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize)
{
	this->map = map;
	this->colMap = colMap;
	this->mapSize = mapSize;
	this->randomiser = randomiser;
}

Enemy* CemeteryEnemyFactory::createEnemy()
{
	sf::Vector2f generatedMobPosition(0.0f, 0.0f);
	generatedMobPosition = randomEnemyPos();
	int rngNumber = randomiser.getInt(100);
	if (rngNumber < 10)
	{
		return (Enemy*)new Bat(5, generatedMobPosition, 1.9);
	}
	else if (rngNumber < 55)
	{
		return (Enemy*)new Skeleton(15, generatedMobPosition, 1.8);
	}
	else
	{
		return (Enemy*)new Ghost(10, generatedMobPosition, 2.4);
	}
}

std::string CemeteryEnemyFactory::factoryName()
{
	return "Cemetery";
}