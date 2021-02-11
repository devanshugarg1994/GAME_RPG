#include "stdafx.h"

#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeU = 50;
	this->maxSize.x = 5000;
	this->maxSize.y = 5000;

	for (size_t x = 0; x < this->maxSize.x; x++) {
		this->map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y = 0; y < this->maxSize.y; y++) {

		}
	}
}

TileMap::~TileMap()
{
}
