#pragma once
#include <SFML/System/Vector2.hpp>

class Rng;

class NuclearWalker
{

public:
	NuclearWalker(Rng* rng, sf::Vector2i mapSize, sf::Vector2i position);
	void RngDirection();
	sf::Vector2i Walk();
	sf::Vector2i getPos();

private:
	sf::Vector2i dir, position, mapSize;
	Rng *rng;
};