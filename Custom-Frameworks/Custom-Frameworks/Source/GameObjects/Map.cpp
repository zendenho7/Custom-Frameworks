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
	: D_RoundedRectangle(color, size, pos, 0.0f, rounding, Drawables::Origin::CENTER)
{
}

Map::Grid::Grid(sf::Vector2<size_t>const& cellCount, sf::Vector2f const& gridPos, sf::Vector2f const& gridBorder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Vector2f const& cellSize, float cellGap)
	: gridSize{ cellSize.x * cellCount.x, cellSize.y * cellCount.y }, gridContainer(gridColor, gridSize, gridPos)
{
	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x) - (cellGap / 2) + gridSize.x) / gridSize.x, ((gridBorder.y) - (cellGap / 2) + gridSize.y) / gridSize.y);

	//Calculate Grid Offset
	sf::Vector2f offset{ gridPos.x - (gridSize.x / 2), gridPos.y - (gridSize.y / 2) };
	
	//Initialize Grid
	gridArray.resize(cellCount.y);
	sf::Vector2f cellPos{ cellSize.x / 2,  cellSize.y / 2 };
	for (size_t i{ 0 }; i < cellCount.y; i++, cellPos.y += cellSize.y) {
		gridArray[i].reserve(cellCount.x);
		cellPos.x = cellSize.x / 2;
		for (size_t j{ 0 }; j < cellCount.x; j++, cellPos.x += cellSize.x) {
			//!!!!!!Refactor Cell Pos
			gridArray[i].emplace_back(cellColor, cellSize, cellPos);
			gridArray[i][j].setPosition(gridArray[i][j].getPosition() + offset);
			gridArray[i][j].setScale((cellSize.x - (cellGap / 2)) / cellSize.x, (cellSize.y - (cellGap / 2)) / cellSize.y);
		}
	}
}

void Map::Grid::drawGrid() {

	//Draw Grid Container
	exEvents->window.draw(gridContainer);

	//Draw Grid
	for (size_t i = 0; i < gridArray.size(); i++) {
		for (size_t j = 0; j < gridArray[i].size(); j++) {
			exEvents->window.draw(gridArray[i][j]);
		}
	}
}
