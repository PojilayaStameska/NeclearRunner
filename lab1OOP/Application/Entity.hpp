#pragma once

#include "../Map/Tile.hpp"
#include "../Map/CollisionMap.hpp"

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Entity 
{
	public:
	virtual void takeDamage(int damage);
	virtual void takeDOT();
	virtual void die() = 0;
	virtual void move(sf::Time dt, CollisionMap* collisionMap) = 0;
	virtual void attack(Entity* hero) = 0;


	//properties
	void setMaxHp(const int hp);
	int MaxHp();
	void setCurHp(const int hp);
	int CurHp();
	void setSpeed(const float spd);
	float Speed();
	void setName(const std::string newName);
	std::string Name();
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f Position();
	void setRotation(const float rotation);
	float Rotation();
	void setIsAlive(bool aliveStatus);
	bool IsAlive();
	Tile CurTile();
	void setCurTile(Tile newTile);
	void setHitTimeout(int millisec);
	int getHitTimeout();


protected:
	Tile basicTile;
	float frameNumber;
	int rotationTileInc;
	sf::Vector2f position;
	float rotation, speed; // rotation - 0.0 equal East 
	std::string name;
	int maxHp, currentHp, damage , hitTimeout;

	bool isPoisoned, isBurning, isAlive;
	float poisonDamageTaken, fireDamageTaken;
};