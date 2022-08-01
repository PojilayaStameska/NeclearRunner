#pragma once
#include "Entity.hpp"
#include "../Generator/Factories/IEnemyFactory.hpp"
#include "Hero.hpp"
#include "../Map/CollisionMap.hpp"
#include "../Map/map.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <memory> // unique_ptr
#include <vector>

class ListEntity : public sf::Drawable, public sf::Transformable
{
public:
	ListEntity(int Size, const sf::Texture& tileset, const sf::Vector2i& entityTileset, Hero* hero, IEnemyFactory* enemyFactory);
	void AddNewEntity();
	void load(sf::Vector2f cameraShift);
	void move(sf::Time dt, CollisionMap* collisionMap);
	void regenerateEnemy(IEnemyFactory* enemyFactory);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const ;



	int startEnemyNumber;
	std::vector<Entity*> entityVector;

	const sf::Texture& entityTileset;
	const sf::Vector2i tileSize;
	std::vector<sf::Vertex> vertices;
};