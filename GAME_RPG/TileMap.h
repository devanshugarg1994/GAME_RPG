#pragma once
#include "Tile.h"

class TileMap
{
private:
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile>>> map;
public:
	TileMap();
	virtual ~TileMap();
};

