/*****************************************************************************************************************
@file         Map.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file for map objects declarations

Copyright � 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Utils.hpp"

namespace Map {
	// ================================================================================
	// Class: Cell
	// ================================================================================
	class Cell : public Drawables::D_RoundedRectangle {
	private:
		//Flag For If Cell Is Selected
		bool b_selected;

		//Default Color
		sf::Color defColor;

		//Clicked Color
		sf::Color clickedColor;

	public:
		//Ddefault Cell Constructor
		Cell() : b_selected{ false } {}

		//Cell Constructor
		Cell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);

		//Default Copy Constructor
		Cell(Cell const& copy) = default;

		//Default Copy Assignment
		Cell& operator=(Cell const& copy) = default;

		//Init Cell
		void initCell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);
		void initCell(Cell const& copy);

		//Is Cell Clicked
		bool isCellClicked();

		//Get Selected
		bool getCellSelected() const;

		//Set Selected
		void setCellSelected(bool selected);

		//Get Default Color
		sf::Color const& getDefColor() const;

		//Set Def Color
		void setDefColor(sf::Color const& color);

		//Get Clicked Color
		sf::Color const& getClickedColor() const;

		//Set Clicked Color
		void setClickedColor(sf::Color const& color);

		//Data Serialization & Deserialization
		virtual std::string serialize() const override;
		virtual void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};
	
	// ================================================================================
	// Class: Grid
	// ================================================================================
	class Grid {
	private:
		//Grid Count
		sf::Vector2<size_t> cellCount;

		//Size Of Grid
		sf::Vector2f gridSize;

		//Grid Border
		sf::Vector2f gridBorder;

		//Cell Gap
		float cellGap;

		//Grid Container
		Drawables::D_RoundedRectangle gridContainer;

		//Array Of Cells
		std::vector<std::vector<Cell>> gridArray;

		//Private Reorganising Of Grid
		void reorganiseGrid();

	public:
		//Ddefault Grid Constructor
		Grid() = default;

		//Grid Constructor
		Grid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap);

		//Resize & Position Grid
		void initGrid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap);

		//Get Cell Count
		sf::Vector2<size_t> getGridCellCount() const;

		//Set Cell Count
		void setGridCellCount(sf::Vector2<size_t> const& cellcount);

		//Get Cell Size
		sf::Vector2f getGridCellSize() const;

		//Set Cell Size
		void setGridCellSize(sf::Vector2f const& cellsize);

		//Get Grid Size
		sf::Vector2f getGridSize() const;

		//Get Grid Pos
		sf::Vector2f getGridPos() const;

		//Set Grid Pos
		void setGridPos(sf::Vector2f const& pos);

		//Get Grid Border
		sf::Vector2f getGridBorder() const;

		//Set Grid Border
		void setGridBorder(sf::Vector2f const& gridborder);

		//Get Cell Gap
		float getGridCellGap() const;

		//Set Cell Gap
		void setGridCellGap(float cellgap);

		//Get Grid Rounding
		float getGridRounding() const;

		//Set Grid Rounding
		void setGridRounding(float rounding);

		//Get Grid Rounding
		float getGridCellRounding() const;

		//Set Grid Rounding
		void setGridCellRounding(float rounding);

		//Get Grid Color
		sf::Color const& getGridColor() const;

		//Set Grid Color
		void setGridColor(sf::Color const& color);

		//Get Cell Default Color
		sf::Color const& getGridCellDefColor() const;

		//Set Cell Def & Clicked Color
		void setGridCellDefColor(sf::Color const& color);

		//Get Cell Clicked Color
		sf::Color const& getGridCellClickedColor() const;

		//Set Cell Def & Clicked Color
		void setGridCellClickedColor(sf::Color const& color);

		//Get Selected
		bool getCellSelected(size_t x, size_t y) const;

		//Set Selected
		void setCellSelected(size_t x, size_t y, bool selected);

		//Get Default Color
		sf::Color getCellColor(size_t x, size_t y) const;

		//Set Def Color
		void setCellColor(size_t x, size_t y,sf::Color const& color);

		//Check If Cell Is Clicked
		void updateIsGridClicked();

		//Reset All Cells Within Grid
		void resetGrid();

		//Draw Grid
		void drawGrid();

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
	};
}

#endif // !MAP_HPP