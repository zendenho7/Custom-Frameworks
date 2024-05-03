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

		void setCell(sf::Color const& defcolor, sf::Color const& clickedcolor, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);
		void setCell(Cell const& copy);

		//Is Cell Clicked
		void cellClicked();

		//Is Cell Selected
		bool cellSelected() const;

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

		//Get Cell Count
		sf::Vector2<size_t> getCellCount() const;

		//Set Cell Count
		void setCellCount(sf::Vector2<size_t> const& cellcount);

		//Get Cell Count
		sf::Vector2f getCellSize() const;

		//Set Cell Count
		void setCellSize(sf::Vector2f const& cellsize);

		//Update Grid
		void updateGrid();

		//Draw Grid
		void drawGrid();
	};
}

#endif // !MAP_HPP