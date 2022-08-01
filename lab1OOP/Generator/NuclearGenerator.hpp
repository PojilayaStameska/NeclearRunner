#pragma once
#include <vector>
class Map;
class Rng;
class NuclearWalker;

class NuclearGenerator
{
public:
	NuclearGenerator(int width, int height);
	void GenerateMap(Map& map, Rng& rng);

protected:
	Rng* rng;
	Map* map;


private:

	struct Walkerslist {
		NuclearWalker* walker = nullptr;
		Walkerslist* next = nullptr;
	} walkers;

	void GenereteFloor();
	void GenereteWalls();
	Walkerslist* deleteWalker(Walkerslist* root, Walkerslist* toDel);
	void addNewWalker(Walkerslist* root);
	int width, height, walkerCount, curWalkers = 0;
	float  walkerSpawnRate, walkerDieRate, mapSmooth, changeDirRate;


};
