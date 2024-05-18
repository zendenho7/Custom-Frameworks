/*****************************************************************************************************************
@file         Map.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file for map objects declarations
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef MAP_HPP
#define MAP_HPP

#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Utils.hpp"

namespace Map {

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
		Cell() = default;

		//Cell Constructor
		Cell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);
		Cell(Cell const& copy);

		//Set Cell
		void setCell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);
		void setCell(Cell const& copy);

		//Is Cell Clicked
		bool isCellClicked();

		//Get Selected
		bool getCellSelected() const;

		//Set Selected
		void setCellSelected(bool seleceted);

		//Get Default Color
		sf::Color const& getDefColor() const;

		//Get Clicked Color
		sf::Color const& getClickedColor() const;

		//Set Def Color
		void setDefColor(sf::Color const& color);

		//Set Clicked Color
		void setClickedColor(sf::Color const& color);
	};
	
	class Grid {
	private:

		//Grid Count
		sf::Vector2<size_t> cellCount;

		//Size Of Grid
		sf::Vector2f gridSize;

		//Array Of Cells
		std::vector<std::vector<Cell>> gridArray;

		//Grid Container
		Drawables::D_RoundedRectangle gridContainer;

		//Grid Border
		sf::Vector2f gridBorder;

		//Cell Gap
		float cellGap;

		//Private Reorganising Of Grid
		void reorganiseGrid();

	public:
		//Ddefault Grid Constructor
		Grid() = default;

		//Grid Constructor
		Grid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap);

		//Resize & Position Grid
		void setGrid(sf::Vector2<size_t>const& cellcount, sf::Vector2f const& gridPos, sf::Vector2f const& gridborder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Color const& cellClickedColor, sf::Vector2f const& cellSize, float cellgap);

		//Modify Cell
		Cell& modifyCell(sf::Vector2<size_t> const& index);

		//Get Cell
		Cell const& getCell(sf::Vector2<size_t> const& index) const;

		//Get Cell Count
		sf::Vector2<size_t> getCellCount() const;

		//Set Cell Count
		void setCellCount(sf::Vector2<size_t> const& cellcount);

		//Get Cell Size
		sf::Vector2f getCellSize() const;

		//Set Cell Size
		void setCellSize(sf::Vector2f const& cellsize);

		//Get Grid Size
		sf::Vector2f getGridSize() const;

		//Get Grid Border
		sf::Vector2f getGridBorder() const;

		//Set Grid Border
		void setGridBorder(sf::Vector2f const& gridborder);

		//Get Cell Gap
		float getCellGap() const;

		//Set Cell Gap
		void setCellGap(float cellgap);

		//Get Grid Rounding
		float getGridRounding() const;

		//Set Grid Rounding
		void setGridRounding(float rounding);

		//Get Grid Rounding
		float getCellRounding() const;

		//Set Grid Rounding
		void setCellRounding(float rounding);

		//Get Grid Color
		sf::Color const& getGridColor() const;

		//Set Grid Color
		void setGridColor(sf::Color const& color);

		//Get Cell Default Color
		sf::Color const& getCellDefColor() const;

		//Get Cell Clicked Color
		sf::Color const& getCellClickedColor() const;

		//Set Cell Def & Clicked Color
		void setCellDefColor(sf::Color const& color);

		//Set Cell Def & Clicked Color
		void setCellClickedColor(sf::Color const& color);

		//Check If Cell Is Clicked
		void checkCellClicked();

		//Reset All Cells Within Grid
		void resetGrid();

		//Draw Grid
		void drawGrid();
	};
}

#endif // !MAP_HPP