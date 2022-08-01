#pragma once
#include "../Enemy.hpp"

class Spider :Enemy
{
public:
	Spider(int hp, sf::Vector2f pos, float spd);
	void attack(Entity* hero) override;
};