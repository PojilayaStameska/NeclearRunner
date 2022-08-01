#include "Application.hpp"
#include "WindowsHelper.hpp"

#include "../Generator/Factories/ArahnidNestEnemyFactory.hpp"
#include "../Generator/Factories/ÑemeteryEnemyFactory.hpp"
#include "../Generator/Factories/SlimeRanchEnemyFactory.hpp"
#include "../Generator/Factories/VampireMansionEnemyFactory.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace
{
	const sf::Vector2i tileSize(64, 64);
	const sf::Vector2i mapSize(2400/tileSize.x,1600/tileSize.y);
}

Application::Application()
	: window(sf::VideoMode(1200, 800), "Map Generator", sf::Style::Fullscreen)
	, map(mapSize.x, mapSize.y)
	, cameraShift(mapSize.x/2 - window.getSize().x/tileSize.x, mapSize.y/2 - window.getSize().y / tileSize.y)
{
	centerWindow(window.getSystemHandle());
	window.setFramerateLimit(75);
	tileSet.loadFromFile("newset.png");
	entityTileSet.loadFromFile("EntityTileset.png");
	HeartTexture.loadFromFile("Heart.png");

	hero = new Hero(sf::Vector2f(mapSize.x / 2, mapSize.y / 2));
	collisionMap = new CollisionMap(mapSize.x, mapSize.y);
	registerEnemyFactories();

	entityList = std::make_unique<ListEntity>(mapSize.x*mapSize.y*0.02, entityTileSet, tileSize, hero, (IEnemyFactory*)(enemyFactories[currentEnemyFactory]));
	tilemap = std::make_unique<Tilemap>(tileSet, tileSize);
	nuclearGenerator = std::make_unique<NuclearGenerator>(mapSize.x, mapSize.y);


	generateMap();
}

void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{


		sf::Time dt = clock.restart();

		processInput(dt);
		update(dt);
		render();
	}
}

void Application::processInput(sf::Time dt)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				rng.reset();
				generateMap();
			}

		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{

			case sf::Keyboard::Subtract:
				selectPreviousEnemyFactory();
				break;

			case sf::Keyboard::Add:
				selectNextEnemyFactory();
				break;
			case sf::Keyboard::Escape:
				window.close();
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		hero->setRotation(270.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			hero->setRotation(315.0f);
		else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			hero->setRotation(225.0f);
		hero->move(dt, collisionMap);
	}

	else

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		hero->setRotation(90.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			hero->setRotation(45.0f);
		else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				hero->setRotation(135.0f);
		hero->move(dt, collisionMap);
	}

	else

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		hero->setRotation(180.0f);
		hero->move(dt, collisionMap);
	}
		
	else

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		hero->setRotation(0.0f);
		hero->move(dt, collisionMap);
	}


}

void Application::update(sf::Time dt)
{
	entityList->move(dt, collisionMap);

	cameraShift = sf::Vector2f(hero->Position().x - window.getSize().x / 2 / tileSize.x, hero->Position().y - window.getSize().y / 2 / tileSize.y);

	entityList->load(cameraShift);
	tilemap->load(map, cameraShift);
	if (hero->CurHp() == 0)
		generateMap();
}

void Application::render()
{
	sf::Vertex* vertices;
	vertices = new sf::Vertex[hero->MaxHp() * 2];
	int hp = hero->CurHp();
	for (int i = 0; i < 3; i++)
	{
		vertices[i * 4].position = sf::Vector2f(10 + i * 40 , 10);
		vertices[i * 4 + 1].position = sf::Vector2f(10 + i * 40, 42);
		vertices[i * 4 + 2].position = sf::Vector2f(42 + i * 40, 42);
		vertices[i * 4 + 3].position = sf::Vector2f(42 + i * 40, 10);
		
		if (hp > 1)
		{
			vertices[i * 4].texCoords = sf::Vector2f(0, 0);
			vertices[i * 4 + 1].texCoords = sf::Vector2f(0, 16);
			vertices[i * 4 + 2].texCoords = sf::Vector2f(16, 16);
			vertices[i * 4 + 3].texCoords = sf::Vector2f(16, 0);
			hp = hp - 2;
		}
		else
		{
			vertices[i * 4].texCoords = sf::Vector2f( 32 - hp * 16, 0);
			vertices[i * 4 + 1].texCoords = sf::Vector2f(32 - hp * 16, 16);
			vertices[i * 4 + 2].texCoords = sf::Vector2f(32 - hp * 16 + 16, 16);
			vertices[i * 4 + 3].texCoords = sf::Vector2f(32 - hp * 16 + 16, 0);
			hp = hp - hp;
		}

	}
	sf::RenderStates states;
	states.texture = &HeartTexture;

	window.clear();
	window.draw(*tilemap);
	window.draw(*entityList);
	window.draw(&vertices[0], hero->MaxHp() * 2, sf::Quads, states);
	window.display();
}

void Application::selectNextEnemyFactory()
{
	currentEnemyFactory = (currentEnemyFactory + 1) % enemyFactories.size();
	rng.reset();
	generateMap();
}

void Application::selectPreviousEnemyFactory()
{
	currentEnemyFactory = (currentEnemyFactory + enemyFactories.size() - 1) % enemyFactories.size();
	rng.reset();
	generateMap();
}

void Application::generateMap()
{
	nuclearGenerator->GenerateMap(map, rng);

	for (int x = 0; x < mapSize.x; x++)
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			collisionMap->setCollision(x, y, map.isWall(x, y));
		}

	}
	hero->setPosition(sf::Vector2f(mapSize.x / 2, mapSize.y / 2));
	hero->setCurHp(6);
	hero->setSpeed(4.2);
	entityList->regenerateEnemy((IEnemyFactory*)(enemyFactories[currentEnemyFactory]));
	cameraShift = sf::Vector2f(mapSize.x/2 - window.getSize().x/tileSize.x, mapSize.y/2 - window.getSize().y / tileSize.y);
	tilemap->load(map, cameraShift);
	entityList->load(cameraShift);
	std::cout << "Welcome to " << enemyFactories[currentEnemyFactory]->factoryName() << '\n';
}

void Application::registerEnemyFactories()
{
	enemyFactories.emplace_back((IEnemyFactory*)new ArahnidNestEnemyFactory(rng, &map, collisionMap, mapSize));
	enemyFactories.emplace_back((IEnemyFactory*)new SlimeRanchEnemyFactory(rng, &map, collisionMap, mapSize));
	enemyFactories.emplace_back((IEnemyFactory*)new VampireMansionEnemyFactory(rng, &map, collisionMap, mapSize));
	enemyFactories.emplace_back((IEnemyFactory*)new CemeteryEnemyFactory(rng, &map, collisionMap, mapSize));

}