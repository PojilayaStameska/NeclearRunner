#pragma once
#include <SFML/System/Vector2.hpp>

class CollisionMap
{
public:
	CollisionMap(int width, int height);
	CollisionMap(sf::Vector2i mapSize);

	bool getCollision(int x, int y);
	bool getCollision(sf::Vector2i cords);

	void setCollision(int x, int y, bool newState);
	void setCollision(sf::Vector2i cords, bool newState);

private:
	int height, width;
	bool* collison;
};

