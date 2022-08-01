#include "ArahnidNestEnemyFactory.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Skeleton.hpp"

ArahnidNestEnemyFactory::ArahnidNestEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize)
{
	this->map = map;
	this->colMap = colMap;
	this->mapSize = mapSize;
	this->randomiser = randomiser;
}

Enemy* ArahnidNestEnemyFactory::createEnemy()
{
	sf::Vector2f generatedMobPosition(0.0f, 0.0f);
	generatedMobPosition = randomEnemyPos();
	if (randomiser.getInt(100) < 20)
	{
		return (Enemy*)new Skeleton(10, generatedMobPosition, 1.2);
	}
	else
	{
		return (Enemy*)new Spider(3, generatedMobPosition, 2.2);
	}
}

std::string ArahnidNestEnemyFactory::factoryName()
{
	return "Arahnid nest";
}