#pragma once
#include "../Enemy.hpp"

class Slime:Enemy
{
public:
	Slime(int hp, sf::Vector2f pos, float spd);
	void attack(Entity* hero) override;
};