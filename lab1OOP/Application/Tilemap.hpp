#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>

class Map;

class Tilemap : public sf::Drawable, public sf::Transformable
{
public:
	Tilemap(const sf::Texture& tileset, const sf::Vector2i& tileSize);

	void load(const Map& map, sf::Vector2f cameraShift);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const sf::Texture& tileset;
	const sf::Vector2i tileSize;
	std::vector<sf::Vertex> vertices;
};
