#pragma once
#include "../Enemy.hpp"

class Ghost :Enemy
{
public:
	Ghost(int hp, sf::Vector2f pos, float spd);
	void attack(Entity* hero) override;
};