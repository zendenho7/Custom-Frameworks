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

// ================================================================================
// Class: Map Cell
// ================================================================================

Map::Cell::Cell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding)
	: D_RoundedRectangle(defcolor, size, pos, 0.0f, rounding, Drawables::Origin::TOP_LEFT), b_selected{ false }, defColor{ defcolor }, clickedColor{ clickedcolor } {}

Map::Cell::Cell(Cell const& copy)
	: D_RoundedRectangle(copy.defColor, copy.getLocalBounds().getSize(), copy.getPosition(), copy.getRotation(), copy.getCornerRounding(), copy.Custom_GetOrigin()), b_selected{ false }, defColor{ copy.defColor }, clickedColor{ copy.clickedColor } {}

void Map::Cell::setCell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding) {
	setD_RoundedRectangle(defcolor, size, pos, 0.0f, rounding, Drawables::Origin::TOP_LEFT);
	b_selected = false;
	defColor = defcolor;
	clickedColor = clickedcolor;
}

void Map::Cell::setCell(Cell const& copy) {
	setD_RoundedRectangle(copy.defColor, copy.getLocalBounds().getSize(), copy.getPosition(), copy.getRotation(), copy.getCornerRounding(), copy.Custom_GetOrigin());
	b_selected = false;
	defColor = copy.defColor;
	clickedColor = copy.clickedColor;
}

void Map::Cell::cellClicked() {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get Button Bound & Size
	sf::FloatRect buttonObj = getGlobalBounds();

	//Check For Mouse Click Within Bounds
	if (mousePos.x > (buttonObj.left) && //Left Side
		mousePos.x < (buttonObj.left + buttonObj.width) && //Right Side
		mousePos.y >(buttonObj.top) && //Top Side
		mousePos.y < (buttonObj.top + buttonObj.height)) //Bottom Side
	{
		//Check For Mouse Click
		if (exEvents->mouseTriggered(sf::Mouse::Left)) {
			b_selected = !b_selected;
			b_selected ? setFillColor(clickedColor) : setFillColor(defColor);
		}
	}
}

bool Map::Cell::cellSelected() const {
	return getFillColor() == clickedColor;
}

// ================================================================================
// Class: Map Grid
// ================================================================================

Map::Grid::Grid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap)
	:	cellCount{ std::clamp(cellcount.x, static_cast<size_t>(1), std::numeric_limits<size_t>::max()), std::clamp(cellcount.y, static_cast<size_t>(1), std::numeric_limits<size_t>::max()) }, 
		gridSize{ cellSize.x * cellCount.x, cellSize.y * cellCount.y }, gridContainer(gridColor, gridSize, gridPos), gridBorder{ gridborder }, cellGap{ cellgap }
{
	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);

	//Calculate Grid Offset Position
	sf::Vector2f offset{ gridContainer.getPosition().x - (gridSize.x / 2), gridContainer.getPosition().y - (gridSize.y / 2)};
	
	//Initialize Grid
	gridArray.resize(cellCount.y);
	sf::Vector2f cellPos{ 0.0f,  0.0f };
	for (size_t i{ 0 }; i < cellCount.y; cellPos.y += (gridArray[i][0].getGlobalBounds().getSize().y + cellGap), i++) {
		gridArray[i].reserve(cellCount.x);
		cellPos.x = 0.0f;
		for (size_t j{ 0 }; j < cellCount.x; cellPos.x += (gridArray[i][j].getGlobalBounds().getSize().x + cellGap), j++) {
			//Construct Cell
			gridArray[i].emplace_back(cellColor, cellClickedColor, cellSize, cellPos);

			//Offset To GridPosition
			gridArray[i][j].setPosition(gridArray[i][j].getPosition() + offset);

			//Calculate Scale Taking Into Account Cell Gap
			gridArray[i][j].setScale((gridSize.x - ((cellCount.x - 1) * cellGap)) / gridSize.x, (gridSize.y - ((cellCount.y - 1) * cellGap)) / gridSize.y);
		}
	}
}

void Map::Grid::setGrid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap) {
	cellCount = { std::clamp(cellcount.x, static_cast<size_t>(1), std::numeric_limits<size_t>::max()), std::clamp(cellcount.y, static_cast<size_t>(1), std::numeric_limits<size_t>::max()) };
	gridSize = { cellSize.x * cellCount.x, cellSize.y * cellCount.y };
	gridContainer.setD_RoundedRectangle(gridColor, gridSize, gridPos);
	gridBorder = gridborder;
	cellGap = cellgap;
	
	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);

	//Calculate Grid Offset Position
	sf::Vector2f offset{ gridContainer.getPosition().x - (gridSize.x / 2), gridContainer.getPosition().y - (gridSize.y / 2) };

	//Initialize Grid
	gridArray.resize(cellCount.y);
	sf::Vector2f cellPos{ 0.0f,  0.0f };
	for (size_t i{ 0 }; i < cellCount.y; cellPos.y += (gridArray[i][0].getGlobalBounds().getSize().y + cellGap), i++) {
		gridArray[i].reserve(cellCount.x);
		cellPos.x = 0.0f;
		for (size_t j{ 0 }; j < cellCount.x; cellPos.x += (gridArray[i][j].getGlobalBounds().getSize().x + cellGap), j++) {
			//Construct Cell
			gridArray[i].emplace_back(cellColor, cellClickedColor, cellSize, cellPos);

			//Offset To GridPosition
			gridArray[i][j].setPosition(gridArray[i][j].getPosition() + offset);

			//Calculate Scale Taking Into Account Cell Gap
			gridArray[i][j].setScale((gridSize.x - ((cellCount.x - 1) * cellGap)) / gridSize.x, (gridSize.y - ((cellCount.y - 1) * cellGap)) / gridSize.y);
		}
	}
}

void Map::Grid::reorganiseGrid() {

	//Calculate New GridSize
	gridSize = { gridArray[0][0].getLocalBounds().getSize().x * cellCount.x, gridArray[0][0].getLocalBounds().getSize().y * cellCount.y };

	//Set Grid Container
	gridContainer.setD_RoundedRectangle(gridContainer.getFillColor(), gridSize, gridContainer.getPosition());

	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);

	//Calculate Grid Offset Position
	sf::Vector2f offset{ gridContainer.getPosition().x - (gridSize.x / 2), gridContainer.getPosition().y - (gridSize.y / 2) };

	//Initialize Grid
	gridArray.resize(cellCount.y);
	sf::Vector2f cellPos{ 0.0f,  0.0f };
	for (size_t i{ 0 }; i < cellCount.y; cellPos.y += (gridArray[i][0].getGlobalBounds().getSize().y + cellGap), i++) {
		gridArray[i].resize(cellCount.x);
		cellPos.x = 0.0f;
		for (size_t j{ 0 }; j < cellCount.x; cellPos.x += (gridArray[i][j].getGlobalBounds().getSize().x + cellGap), j++) {

			//Set Fill Color
			gridArray[i][j].setCell(gridArray[0][0]);

			//Offset To GridPosition
			gridArray[i][j].setPosition(cellPos + offset);

			//Calculate Scale Taking Into Account Cell Gap
			gridArray[i][j].setScale((gridSize.x - ((cellCount.x - 1) * cellGap)) / gridSize.x, (gridSize.y - ((cellCount.y - 1) * cellGap)) / gridSize.y);
		}
	}
}

sf::Vector2<size_t> Map::Grid::getCellCount() const {
	return { gridArray[0].size(), gridArray.size() };
}

void Map::Grid::setCellCount(sf::Vector2<size_t> const& cellcount) {

	//Clamp Cell Count To Minimum 1
	cellCount = { std::clamp(cellcount.x, static_cast<size_t>(1), std::numeric_limits<size_t>::max()), std::clamp(cellcount.y, static_cast<size_t>(1), std::numeric_limits<size_t>::max()) };

	//Reorganise Grid Based On Top Left Cell
	reorganiseGrid();
}

sf::Vector2f Map::Grid::getCellSize() const {
	return { gridArray[0][0].getLocalBounds().getSize() };
}

void Map::Grid::setCellSize(sf::Vector2f const& cellsize) {

	//Resize Topleft Cell
	gridArray[0][0].setSize(cellsize);

	//Reorganise Grid Based On Top Left Cell
	reorganiseGrid();
}

void Map::Grid::updateGrid() {
	//Update Grid
	for (size_t i = 0; i < gridArray.size(); i++) {
		for (size_t j = 0; j < gridArray[i].size(); j++) {
			gridArray[i][j].cellClicked();
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
