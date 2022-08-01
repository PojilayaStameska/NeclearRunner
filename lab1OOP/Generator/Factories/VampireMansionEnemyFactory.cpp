#include "VampireMansionEnemyFactory.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Bat.hpp"

VampireMansionEnemyFactory::VampireMansionEnemyFactory(Rng& randomiser, Map* map, CollisionMap* colMap, sf::Vector2i mapSize)
{
	this->map = map;
	this->colMap = colMap;
	this->mapSize = mapSize;
	this->randomiser = randomiser;
}

Enemy* VampireMansionEnemyFactory::createEnemy()
{
	sf::Vector2f generatedMobPosition(0.0f, 0.0f);
	generatedMobPosition = randomEnemyPos();
	int rngNumber = randomiser.getInt(100);
	if (rngNumber < 5)
	{
		return (Enemy*)new Ghost(15, generatedMobPosition, 2.1);
	}
	else if (rngNumber < 15)
	{
		return (Enemy*)new Spider(3, generatedMobPosition, 1.9);
	}
	else
	{
		return (Enemy*)new Bat(3, generatedMobPosition, 2.4);
	}
}


std::string VampireMansionEnemyFactory::factoryName()
{
	return "Vampire mansion";
}