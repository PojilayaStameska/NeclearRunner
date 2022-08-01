#include "NuclearGenerator.hpp"
#include "NuclearWalker.hpp"
#include "../Utility/Rng.hpp"
#include "../Map/Map.hpp"

#include <iostream>

NuclearGenerator::NuclearGenerator(int width, int height):
	width(width),
	height(height)
{
    //#TODO read from settings file
	walkerCount = 10;
	walkerSpawnRate = 0.05f;
	walkerDieRate = 0.05f;
	mapSmooth = 0.2f;
	changeDirRate = 0.6f;
}

void NuclearGenerator::addNewWalker(Walkerslist* root)
{
	Walkerslist* curPointer = root;
	while (curPointer != nullptr)
	{
		if (curPointer->next == nullptr)
		{
			curPointer->next = new Walkerslist;
			curPointer->next->walker = new NuclearWalker(rng, sf::Vector2i(width, height), curPointer->walker->getPos());
			curPointer->next->next = nullptr;
			curPointer = curPointer->next;
			break;
		}
		curPointer = curPointer->next;
	}
}

NuclearGenerator::Walkerslist* NuclearGenerator::deleteWalker(Walkerslist* root, Walkerslist* toDel)
{
	Walkerslist* curPointer = root;
	while (curPointer != nullptr)
	{
		if (curPointer->next == toDel)
		{
			Walkerslist* tmp = curPointer->next;
			curPointer->next = curPointer->next->next;
			free(tmp->walker);
			free(tmp);
			return curPointer;
		}
		curPointer = curPointer->next;
	}
}

void NuclearGenerator::GenereteFloor()
{
	NuclearWalker* tmpWalker = new NuclearWalker(rng, sf::Vector2i(width, height), sf::Vector2i(width / 2, height / 2));
	curWalkers = 1;
	int floorCount = 1;
	map->setTile(sf::Vector2i(width / 2, height / 2), Tile::Ground);
	walkers.walker = tmpWalker;
	Walkerslist* curPointer = &walkers;
	int iterations = 0;
	do {
		while (curPointer != nullptr)
		{
			if (rng->getFloat(0, 1) < 0.5 && curWalkers < walkerCount)
			{
 				addNewWalker(&walkers);
				curWalkers++;
			}
			curPointer = curPointer->next;
		}
		curPointer = &walkers;
		while (curPointer != nullptr)
		{
			sf::Vector2i  pos = curPointer->walker->Walk();
			for (int i = 0; i < 1; i++)
			{
				Tile generetedTile = Tile::Unused;
				int rand = rng->getInt(10);
				if (rand < 7)
					generetedTile = Tile::Ground;
				else
					if (rand < 9)
						generetedTile = Tile::GroundOrangeLava;
					else
						generetedTile = Tile::GroundRedLava;
				if (map->getTile(pos + sf::Vector2i(i % 2, i / 2)) == Tile::Unused) {
					floorCount++;
				}
				map->setTile(pos + sf::Vector2i(i % 2, i / 2), generetedTile);
			}
			curPointer = curPointer->next;
		}
		curPointer = &walkers;
		while (curPointer != nullptr)
		{
			if (rng->getFloat(0, 1) < changeDirRate)
			{	
				curPointer->walker->RngDirection();
			}
			curPointer = curPointer->next;
		}
		curPointer = walkers.next;
		while (curPointer != nullptr)
		{
			if (rng->getFloat(0, 1) < walkerDieRate && curWalkers > 1)
			{
				curPointer = deleteWalker(&walkers, curPointer);
				curWalkers--;
			}
			curPointer = curPointer->next;
		}
		float check = (float)floorCount / (float)(width * height);
		if ((float)floorCount / (float)(width * height) > mapSmooth)
			break;
		iterations++;
	} while (iterations < 1000);
}

void NuclearGenerator::GenereteWalls()
{
	for(int x = 0; x < width -1; x++)
		for (int y = 0; y < height - 1; y++)
		{
			Tile thisTile = map->getTile(sf::Vector2i(x, y));
			if (thisTile == Tile::Ground || thisTile == Tile::GroundOrangeLava || thisTile == Tile::GroundRedLava)
			{
				if (map->getTile(sf::Vector2i(x + 1, y)) == Tile::Unused)
					map->setTile(sf::Vector2i(x + 1, y), Tile::Wall);

				if (map->getTile(sf::Vector2i(x - 1, y)) == Tile::Unused)
					map->setTile(sf::Vector2i(x - 1, y), Tile::Wall);

				if (map->getTile(sf::Vector2i(x, y + 1)) == Tile::Unused)
					map->setTile(sf::Vector2i(x, y + 1), Tile::Wall);

				if (map->getTile(sf::Vector2i(x, y - 1)) == Tile::Unused)
					map->setTile(sf::Vector2i(x, y - 1), Tile::Wall);
			}
		}
}

void NuclearGenerator::GenerateMap(Map& map, Rng& rng)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			map.setTile(sf::Vector2i(x, y), Tile::Unused);
	this->rng = &rng;
	this->map = &map;
	GenereteFloor();
	GenereteWalls();
	Walkerslist* curPointer = &walkers;
	while (curWalkers > 1)
	{
		while (curPointer->next != NULL)
		{
			curPointer = curPointer->next;
		}
		if (curPointer != &walkers)
		{
			deleteWalker(&walkers, curPointer);
			curWalkers--;
		}
		curPointer = &walkers;
	}
}