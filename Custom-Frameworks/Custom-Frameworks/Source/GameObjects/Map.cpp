/*****************************************************************************************************************
@file         Map.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for Map objects defintions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\GameObjects\Map.hpp"

// ================================================================================
// Class: Cell
// ================================================================================

Map::Cell::Cell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding)
	: D_RoundedRectangle(defcolor, size, pos, 0.0f, rounding, Drawables::Origin::TOP_LEFT), b_selected{ false }, defColor{ defcolor }, clickedColor{ clickedcolor } {}

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

bool Map::Cell::isCellClicked() {
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
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}

bool Map::Cell::getCellSelected() const {
	return b_selected;
}

void Map::Cell::setCellSelected(bool selected) {
	b_selected = selected;
	
	if (b_selected) {
		setFillColor(clickedColor);
	}
	else {
		setFillColor(defColor);
	}
}

sf::Color const& Map::Cell::getDefColor() const {
	return defColor;
}

sf::Color const& Map::Cell::getClickedColor() const {
	return clickedColor;
}

void Map::Cell::setDefColor(sf::Color const& color) {
	defColor = color;
}

void Map::Cell::setClickedColor(sf::Color const& color) {
	clickedColor = color;
}

std::string Map::Cell::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_RoundedRectangle::serialize() << " " << b_selected << " "
		<< defColor.r << " " << defColor.g << " " << defColor.b << " " << defColor.a << " "
		<< clickedColor.r << " " << clickedColor.g << " " << clickedColor.b << " " << clickedColor.a;

	return oss.str();
}

void Map::Cell::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Input Stream From String
	D_RoundedRectangle::deserialize(iss) >> b_selected 
		>> defColor.r >> defColor.g >> defColor.b >> defColor.a 
		>> clickedColor.r >> clickedColor.g >> clickedColor.b >> clickedColor.a;
}

std::istringstream& Map::Cell::deserialize(std::istringstream& stream) {

	//Input Stream From String
	D_RoundedRectangle::deserialize(stream) >> b_selected 
		>> defColor.r >> defColor.g >> defColor.b >> defColor.a 
		>> clickedColor.r >> clickedColor.g >> clickedColor.b >> clickedColor.a;

	return stream;
}

// ================================================================================
// Class: Map Grid
// ================================================================================

Map::Grid::Grid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap)
	:	cellCount{ std::clamp(cellcount.x, static_cast<size_t>(1), std::numeric_limits<size_t>::max()), std::clamp(cellcount.y, static_cast<size_t>(1), std::numeric_limits<size_t>::max()) }, 
		gridSize{ cellSize.x * cellCount.x, cellSize.y * cellCount.y }, gridBorder{ gridborder }, cellGap{ cellgap }, gridContainer(gridColor, gridSize, gridPos)
{
	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);
	gridContainer.Custom_SetFixedScale();

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
			gridArray[i][j].Custom_SetFixedScale();
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
	gridContainer.Custom_SetFixedScale();

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
			gridArray[i][j].Custom_SetFixedScale();
		}
	}
}

Map::Cell& Map::Grid::modifyCell(sf::Vector2<size_t> const& index) {
	return gridArray[index.y][index.x];
}

Map::Cell const& Map::Grid::getCell(sf::Vector2<size_t> const& index) const {
	return gridArray[index.y][index.x];
}

void Map::Grid::reorganiseGrid() {

	//Calculate New GridSize
	gridSize = { gridArray[0][0].getLocalBounds().getSize().x * cellCount.x, gridArray[0][0].getLocalBounds().getSize().y * cellCount.y };

	//Set Grid Container
	gridContainer.setD_RoundedRectangle(gridContainer.getFillColor(), gridSize, gridContainer.getPosition());

	//Scale Grid Container For Border
	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);
	gridContainer.Custom_SetFixedScale();

	//Calculate Grid Offset Position
	sf::Vector2f offset{ gridContainer.getPosition().x - (gridSize.x / 2), gridContainer.getPosition().y - (gridSize.y / 2) };

	//Resize Y Grid If Cell Count Y Has Changed
	if (cellCount.y != gridArray.size()) {
		gridArray.resize(cellCount.y);
	}

	sf::Vector2f cellPos{ 0.0f,  0.0f };
	for (size_t i{ 0 }; i < cellCount.y; cellPos.y += (gridArray[i][0].getGlobalBounds().getSize().y + cellGap), i++) {

		//Resize X Grid If Cell Count X Has Changed
		if (cellCount.x != gridArray[i].size()) {
			gridArray[i].resize(cellCount.x);
		}

		//Reset CellPosX To Starting Point
		cellPos.x = 0.0f;
		for (size_t j{ 0 }; j < cellCount.x; cellPos.x += (gridArray[i][j].getGlobalBounds().getSize().x + cellGap), j++) {

			//Set Fill Color
			gridArray[i][j].setCell(gridArray[0][0]);

			//Offset To GridPosition
			gridArray[i][j].setPosition(cellPos + offset);

			//Calculate Scale Taking Into Account Cell Gap
			gridArray[i][j].setScale((gridSize.x - ((cellCount.x - 1) * cellGap)) / gridSize.x, (gridSize.y - ((cellCount.y - 1) * cellGap)) / gridSize.y);
			gridArray[i][j].Custom_SetFixedScale();
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

sf::Vector2f Map::Grid::getGridSize() const {
	return gridSize;
}

sf::Vector2f Map::Grid::getGridBorder() const {
	return gridBorder;
}

void Map::Grid::setGridBorder(sf::Vector2f const& gridborder) {
	gridBorder = { std::clamp(gridborder.x, 0.0f, std::numeric_limits<float>::max()), std::clamp(gridborder.y, 0.0f, std::numeric_limits<float>::max()) };;

	gridContainer.setScale(((gridBorder.x * 2) + gridSize.x) / gridSize.x, ((gridBorder.y * 2) + gridSize.y) / gridSize.y);
}

float Map::Grid::getCellGap() const {
	return cellGap;
}

void Map::Grid::setCellGap(float cellgap) {
	cellGap = std::clamp(cellgap, 0.0f, std::min(gridArray[0][0].getLocalBounds().getSize().x, gridArray[0][0].getLocalBounds().getSize().y));

	//Reorganise Grid Based On Top Left Cell
	reorganiseGrid();
}

float Map::Grid::getGridRounding() const {
	return gridContainer.getCornerRounding();
}

void Map::Grid::setGridRounding(float rounding) {
	gridContainer.setCornerRounding(rounding);
}

float Map::Grid::getCellRounding() const {
	return gridArray[0][0].getCornerRounding();
}

void Map::Grid::setCellRounding(float rounding) {
	for (size_t i{ 0 }; i < cellCount.y; i++) {
		for (size_t j{ 0 }; j < cellCount.x; j++) {
			gridArray[i][j].setCornerRounding(rounding);
		}
	}
}

sf::Color const& Map::Grid::getGridColor() const {
	return gridContainer.getFillColor();
}

void Map::Grid::setGridColor(sf::Color const& color) {
	gridContainer.setFillColor(color);
}

sf::Color const& Map::Grid::getCellDefColor() const {
	return gridArray[0][0].getDefColor();
}

sf::Color const& Map::Grid::getCellClickedColor() const {
	return gridArray[0][0].getClickedColor();
}

void Map::Grid::setCellDefColor(sf::Color const& color) {
	for (size_t i{ 0 }; i < cellCount.y; i++) {
		for (size_t j{ 0 }; j < cellCount.x; j++) {
			gridArray[i][j].setDefColor(color);

			if(!gridArray[i][j].getCellSelected())
			gridArray[i][j].setFillColor(color);
		}
	}
}

void Map::Grid::setCellClickedColor(sf::Color const& color) {
	for (size_t i{ 0 }; i < cellCount.y; i++) {
		for (size_t j{ 0 }; j < cellCount.x; j++) {
			gridArray[i][j].setClickedColor(color);

			if (gridArray[i][j].getCellSelected())
				gridArray[i][j].setFillColor(color);
		}
	}
}

void Map::Grid::updateIsGridClicked() {
	//Update Grid
	for (size_t i = 0; i < gridArray.size(); i++) {
		for (size_t j = 0; j < gridArray[i].size(); j++) {
			if (gridArray[i][j].isCellClicked()) {
				gridArray[i][j].setCellSelected(!gridArray[i][j].getCellSelected());
			}
		}
	}
}

void Map::Grid::resetGrid() {
	//Reset All Cells Within Grid
	for (size_t i = 0; i < gridArray.size(); i++) {
		for (size_t j = 0; j < gridArray[i].size(); j++) {
			gridArray[i][j].setCellSelected(false);
		}
	}
}

void Map::Grid::drawGrid() {

	//Draw Grid Container
	if(gridContainer.getFillColor().a > 0)
	exEvents->window.draw(gridContainer);

	//Draw Grid
	for (size_t i = 0; i < gridArray.size(); i++) {
		for (size_t j = 0; j < gridArray[i].size(); j++) {

			if(gridArray[i][j].getFillColor().a > 0)
			exEvents->window.draw(gridArray[i][j]);
		}
	}
}

std::string Map::Grid::serialize() const {
	std::ostringstream oss("");

	oss << cellCount.x << " " << cellCount.y << " " << gridSize.x << " " << gridSize.y << " "
		<< gridBorder.x << " " << gridBorder.y << " " << cellGap << " "
		<< gridContainer.serialize() << " ";

	//Serialize Array Of Cells
	for (std::vector<Cell> const& cellVec : gridArray) {
		for (Cell const& cell : cellVec) {
			oss << cell.serialize() << " ";
		}
	}

	return oss.str();
}

void Map::Grid::deserialize(std::string const& data) {
	std::istringstream iss(data);

	iss >> cellCount.x >> cellCount.y >> gridSize.x >> gridSize.y 
		>> gridBorder.x >> gridBorder.y >> cellGap ;

	gridContainer.deserialize(iss);

	//Serialize Array Of Cells
	for (std::vector<Cell>& cellVec : gridArray) {
		for (Cell& cell : cellVec) {
			cell.deserialize(iss);
		}
	}
}

std::istringstream& Map::Grid::deserialize(std::istringstream& stream) {

	stream >> cellCount.x >> cellCount.y >> gridSize.x >> gridSize.y 
		>> gridBorder.x >> gridBorder.y >> cellGap ;

	gridContainer.deserialize(stream);

	//Serialize Array Of Cells
	for (std::vector<Cell>& cellVec : gridArray) {
		for (Cell& cell : cellVec) {
			cell.deserialize(stream);
		}
	}

	return stream;
}
