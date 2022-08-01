#include "ListEntity.hpp"


#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//size переделать
ListEntity::ListEntity(int Size, const sf::Texture& entityTileset, const sf::Vector2i& tileSize, Hero* hero, IEnemyFactory* enemyFactory)
	: entityTileset(entityTileset)
	, tileSize(tileSize)
	, startEnemyNumber(Size)
{
	entityVector.push_back(hero);
}

void ListEntity::regenerateEnemy(IEnemyFactory* enemyFactory)
{
	Hero* tmp = (Hero*)entityVector[0];
	for (int i = 1; i < entityVector.size(); i++)
	{
		free(entityVector[i]);;
	}
	entityVector.clear();
	entityVector.push_back(tmp);
	for (int i = 0; i < startEnemyNumber; i++)
	{
		entityVector.push_back(enemyFactory->createEnemy());
		
	}
}

void ListEntity::load(sf::Vector2f cameraShift)
{
	vertices.clear();
	vertices.resize(entityVector.size() * 4);
	for (int i = 0; i < entityVector.size(); i++)
	{
		int tileNumber = int(entityVector[i]->CurTile());

		if (tileNumber < 0)
		{	
			std::cout << "IEntity: tileNumber error\n";
			continue;
		}
	
		int tu = tileNumber % (entityTileset.getSize().x / 16);
		int tv = tileNumber / (entityTileset.getSize().x / 16);

		sf::Vertex* quad = &vertices[(entityVector.size() - i - 1) * 4];
		sf::Vector2f entityPos = entityVector[i]->Position();

		quad[0].position = sf::Vector2f((entityPos.x - cameraShift.x + 0.f) * tileSize.x, (entityPos.y - cameraShift.y + 0.f) * tileSize.y);
		quad[1].position = sf::Vector2f((entityPos.x - cameraShift.x + 1.f) * tileSize.x, (entityPos.y - cameraShift.y + 0.f) * tileSize.y);
		quad[2].position = sf::Vector2f((entityPos.x - cameraShift.x + 1.f) * tileSize.x, (entityPos.y - cameraShift.y + 1.f) * tileSize.y);
		quad[3].position = sf::Vector2f((entityPos.x - cameraShift.x + 0.f) * tileSize.x, (entityPos.y - cameraShift.y + 1.f) * tileSize.y);


		//TODO объеденить texture и размер тайла на ней в единый объект и передавать его
		quad[0].texCoords = sf::Vector2f((tu + 0.f) * 16, (tv + 0.f) * 16);
		quad[1].texCoords = sf::Vector2f((tu + 1.f) * 16, (tv + 0.f) * 16);
		quad[2].texCoords = sf::Vector2f((tu + 1.f) * 16, (tv + 1.f) * 16);
		quad[3].texCoords = sf::Vector2f((tu + 0.f) * 16, (tv + 1.f) * 16);
	}
}

void ListEntity::move(sf::Time dt, CollisionMap* collisionMap)
{
	for (int i = 1; i < entityVector.size(); i++)
	{
		entityVector[i]->move(dt, collisionMap);

		sf::Vector2f monsterPos = entityVector[0]->Position();
		sf::Vector2f heroPos = entityVector[i]->Position();

		if ((monsterPos.x + 0.2 <= heroPos.x + 0.85 && monsterPos.x + 0.2 >= heroPos.x + 0.2) && (monsterPos.y + 0.5 <= heroPos.y + 0.98 && monsterPos.y + 0.5 >= heroPos.y + 0.5))
			entityVector[i]->attack(entityVector[0]);
		if ((monsterPos.x + 0.85 <= heroPos.x + 0.85 && monsterPos.x + 0.85 >= heroPos.x + 0.2) && (monsterPos.y + 0.5 <= heroPos.y + 0.98 && monsterPos.y +0.5 >= heroPos.y + 0.5))
			entityVector[i]->attack(entityVector[0]);
		if ((monsterPos.x + 0.2 <= heroPos.x + 0.85 && monsterPos.x + 0.2 >= heroPos.x + 0.2) && (monsterPos.y + 0.98 <= heroPos.y + 0.98 && monsterPos.y + 0.98 >= heroPos.y + 0.5))
			entityVector[i]->attack(entityVector[0]);
		if ((monsterPos.x + 0.85 <= heroPos.x + 0.85 && monsterPos.x + 0.85 >= heroPos.x + 0.2) && (monsterPos.y + 0.98 <= heroPos.y + 0.98 && monsterPos.y + 0.98 >= heroPos.y + 0.5))
			entityVector[i]->attack(entityVector[0]);
	}
	entityVector[0]->setHitTimeout(entityVector[0]->getHitTimeout() - dt.asMilliseconds());
}

void ListEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &entityTileset;
	target.draw(&vertices[0], vertices.size(), sf::Quads, states);
}

