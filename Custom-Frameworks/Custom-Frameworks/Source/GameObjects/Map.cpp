/*****************************************************************************************************************
@file         Map.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for Map objects defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\GameObjects\Map.hpp"

Map::Cell::Cell(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding)
	: D_RoundedRectangle(color, size, pos, rounding)
{
}

Map::Grid::Grid(sf::Vector2<size_t>const& gridCount, sf::Vector2f const& gridPos, sf::Color const& cellColor, sf::Vector2f const& cellSize, float cellRounding) {
	
	//Initialize Grid
	gridArray.resize(gridCount.y);
	for (size_t i{ 0 }; i < gridCount.y; i++) {
		gridArray[i].reserve(gridCount.x);
		for (size_t j{ 0 }; j < gridCount.x; j++) {
			//!!!!!!Refactor Cell Pos
			gridArray[i].emplace_back(cellColor, cellSize, gridPos, cellRounding);
		}
	}
}