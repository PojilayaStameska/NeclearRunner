#include "Tilemap.hpp"
#include "../Map/Map.hpp"
#include "../Utility/Utility.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Tilemap::Tilemap(const sf::Texture& tileset, const sf::Vector2i& tileSize)
	: tileset(tileset)
	, tileSize(tileSize)
{
}

void Tilemap::load(const Map& map, sf::Vector2f cameraShift)
{
	vertices.clear();
	vertices.resize(map.width * map.height * 4);

	for (int y = 0; y < map.height; ++y)
		for (int x = 0; x < map.width; ++x)
		{
			int tileNumber = (int)map.getTile(x, y);

			if (tileNumber < 0)
				continue;

			int tu = tileNumber % (tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (tileset.getSize().x / tileSize.x);

			sf::Vertex* quad = &vertices[(x + y * map.width) * 4];

			quad[0].position = sf::Vector2f((x - cameraShift.x + 0.f) * tileSize.x, (y - cameraShift.y + 0.f) * tileSize.y);
			quad[1].position = sf::Vector2f((x - cameraShift.x + 1.f) * tileSize.x, (y - cameraShift.y + 0.f) * tileSize.y);
			quad[2].position = sf::Vector2f((x - cameraShift.x + 1.f) * tileSize.x, (y - cameraShift.y + 1.f) * tileSize.y);
			quad[3].position = sf::Vector2f((x - cameraShift.x + 0.f) * tileSize.x, (y - cameraShift.y + 1.f) * tileSize.y);


			//TODO объеденить texture и размер тайла на ней в единый объект и передавать его
			quad[0].texCoords = sf::Vector2f((tu + 0.f) * 36, (tv + 0.f) * 36);
			quad[1].texCoords = sf::Vector2f((tu + 1.f) * 36, (tv + 0.f) * 36);
			quad[2].texCoords = sf::Vector2f((tu + 1.f) * 36, (tv + 1.f) * 36);
			quad[3].texCoords = sf::Vector2f((tu + 0.f) * 36, (tv + 1.f) * 36);
		}
}


void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(&vertices[0], vertices.size(), sf::Quads, states);
}
