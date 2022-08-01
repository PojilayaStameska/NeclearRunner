#pragma once
#include "Entity.hpp"
#include "Hero.hpp"
class Enemy : public Entity
{

public:
	virtual void die() override;
	virtual void move(sf::Time dt, CollisionMap* collisionMap) override;
protected:

private:
};