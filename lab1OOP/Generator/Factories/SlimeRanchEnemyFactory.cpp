#include "SlimeRanchEnemyFactory.hpp"
#include "../../Application/Enemy/Slime.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Skeleton.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Bat.hpp"

SlimeRanchEnemyFactory::SlimeRanchEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize)
{
	this->map = map;
	this->colMap = colMap;
	this->mapSize = mapSize;
	this->randomiser = randomiser;
}

Enemy* SlimeRanchEnemyFactory::createEnemy()
{
	sf::Vector2f generatedMobPosition(0.0f, 0.0f);
	generatedMobPosition = randomEnemyPos();
	int rngNumber = randomiser.getInt(100);
	if (rngNumber < 2)
	{
		return (Enemy*)new Skeleton(10, generatedMobPosition, 0.8);
	}
	else if (rngNumber < 3)
	{
		return (Enemy*)new Bat(3, generatedMobPosition, 1.7);
	}
	else if (rngNumber < 5)
	{
		return (Enemy*)new Ghost(10, generatedMobPosition, 1);
	}
	else if (rngNumber < 10)
	{
		return (Enemy*)new Spider(3, generatedMobPosition, 1.7);
	}
	else
	{
		return (Enemy*)new Slime(10, generatedMobPosition, 2);
	}
}

std::string SlimeRanchEnemyFactory::factoryName()
{
	return "Slime ranch";
}