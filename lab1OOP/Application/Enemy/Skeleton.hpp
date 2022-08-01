#pragma once
#include "../Enemy.hpp"

class Skeleton :Enemy
{
public:
	Skeleton(int hp, sf::Vector2f pos, float spd);
	void attack(Entity* hero) override;
};