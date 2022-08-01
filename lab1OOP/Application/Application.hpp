#pragma once

#include "Tilemap.hpp"
#include "Hero.hpp"
#include "ListEntity.hpp"
#include "../Map/CollisionMap.hpp"
#include "../Generator/NuclearGenerator.hpp"
#include "../Map/Map.hpp"
#include "../Utility/Rng.hpp"
#include "../Generator/Factories/IEnemyFactory.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory> // unique_ptr

class Application
{
public:
	Application();

	void run();

private:
	void processInput(sf::Time dt);
	void update(sf::Time dt);
	void render();

	void registerEnemyFactories();
	void selectNextEnemyFactory();
	void selectPreviousEnemyFactory();

	void generateMap();


private:
	sf::RenderWindow window;
	sf::Texture tileSet;
	sf::Texture entityTileSet;
	sf::Texture HeartTexture;
	sf::Font font;
	sf::Vector2f cameraShift;
	Map map;
	Rng rng;
	Hero* hero;
	CollisionMap* collisionMap;

	std::unique_ptr<Tilemap> tilemap;
	std::unique_ptr<NuclearGenerator> nuclearGenerator;
	std::unique_ptr<ListEntity> entityList;

	std::vector<IEnemyFactory*> enemyFactories;
	int currentEnemyFactory = 0;
	
};
