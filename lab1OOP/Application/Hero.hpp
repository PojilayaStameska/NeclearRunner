#pragma once
#include "Entity.hpp"
#include "../Map/CollisionMap.hpp"

class Hero: public Entity 
{
public:
	Hero(sf::Vector2f Startposition);
	bool getAliveState();
	virtual void die() override;
	virtual void move(sf::Time dt, CollisionMap* collisionMap) override;
	int getPoints();
	void setPoints(int points);
	void attack(Entity* monster) override;
private:
	bool isAlive;
	int points;
};