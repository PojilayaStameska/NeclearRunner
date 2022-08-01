#pragma once
#include "../Enemy.hpp"

class Bat :Enemy
{
public:
	Bat(int hp, sf::Vector2f pos, float spd);
	void attack(Entity* hero) override;
};