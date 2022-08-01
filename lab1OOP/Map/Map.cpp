#include "Map.hpp"

#include <algorithm> // fill
#include <utility> // move

Map::Map(int width, int height)
	: width(width)
	, height(height)
	, tiles(width * height, Tile::Unused)
{
}

void Map::setTile(int x, int y, Tile tile)
{
	tiles[x + y * width] = tile;
}

void Map::setTile(const sf::Vector2i& pos, Tile tile)
{
	setTile(pos.x, pos.y, tile);
}

Tile Map::getTile(int x, int y) const
{
	return tiles[x + y * width];
}

Tile Map::getTile(const sf::Vector2i& pos) const
{
	return getTile(pos.x, pos.y);
}

bool Map::isWall(int x, int y) const
{
	if (tiles[x + y * width] == Tile::Wall)
		return true;
	else
		return false;
}

void Map::fill(Tile tile)
{
	std::fill(tiles.begin(), tiles.end(), tile);
}

void Map::move(std::vector<Tile>&& tiles)
{
	this->tiles = std::move(tiles);
}

std::vector<Tile> Map::copy()
{
	return tiles;
}
