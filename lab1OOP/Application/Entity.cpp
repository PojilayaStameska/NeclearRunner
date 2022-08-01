#pragma once
#include "Entity.hpp"
#include <iostream>

void Entity::setMaxHp(const int hp)
{
	if (hp < 0)
		this->maxHp = 1;
	else
		this->maxHp = hp;
}

int Entity::MaxHp()
{
	return maxHp;
}

void Entity::setCurHp(const int hp)
{
	if (hp < 0)
	{
		die();
		currentHp = 0;
	}
	else
		this->currentHp = hp;
}

int Entity::CurHp()
{
	return currentHp;
}

void Entity::setSpeed(const float spd)
{
	if (spd < 0)
		this->speed = 0.0;
	else
		this->speed = spd;
}

float Entity::Speed()
{
	return speed;
}

void Entity::setName(const std::string newName)
{
	this->name = newName;
}

std::string Entity::Name()
{
	return name;
}

void Entity::takeDamage(int damage)
{
	setCurHp(CurHp() - damage);
	hitTimeout = 800;
}

void Entity::takeDOT()
{
	if (isBurning)
		takeDamage(fireDamageTaken);
	if (isPoisoned)
		takeDamage(poisonDamageTaken);
}

sf::Vector2f Entity::Position()
{
	return position;
}

void Entity::setPosition(sf::Vector2f newPosition)
{
	if (newPosition.x > 0 && newPosition.y > 0)
		this->position = newPosition;
}

float Entity::Rotation()
{
	return rotation;
}

void Entity::setRotation(const float rotation)
{
	if (rotation <= 360 && rotation >= 0)
	{
		this->rotation = rotation;
	}
	else
	{
		std::cout << "Wrong rotation set register";
	}
}

bool Entity::IsAlive()
{
	return isAlive;
}

void Entity::setIsAlive(bool aliveStatus)
{
	isAlive = aliveStatus;
}


Tile Entity::CurTile()
{
	return (Tile)((int)basicTile + (int)frameNumber + rotationTileInc);
}

void Entity::setCurTile(Tile newTile)
{
	basicTile = newTile;
}

void Entity::setHitTimeout(int millisec)
{
	hitTimeout = millisec;
}

int Entity::getHitTimeout()
{
	return hitTimeout;
}