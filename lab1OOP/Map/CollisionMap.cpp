#include "CollisionMap.hpp"


CollisionMap::CollisionMap(int width, int height):
	width(width),
	height(height)
{
	collison = new bool[width * height]{ false };
}

CollisionMap::CollisionMap(sf::Vector2i mapSize)
{
	CollisionMap(mapSize.x, mapSize.y);
}

bool CollisionMap::getCollision(int x, int y)
{
	return collison[x + y * width];
}

bool CollisionMap::getCollision(sf::Vector2i cords)
{
	return getCollision(cords.x, cords.y);
}

void CollisionMap::setCollision(int x, int y, bool newState)
{
	collison[x + y * width] = newState;
}

void CollisionMap::setCollision(sf::Vector2i cords, bool newState)
{
	setCollision(cords.x, cords.y, newState);
}