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

	public:
		//Ddefault Cell Constructor
		Cell() = default;

		//Cell Constructor
		Cell(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f);
	};
	
	class Grid {
	private:
		//Array Of Cells
		std::vector<std::vector<Cell>> gridArray;

		//Size Of Grid
		sf::Vector2f gridSize;

		//Grid Container
		Drawables::D_RoundedRectangle gridContainer;

	public:
		//Ddefault Grid Constructor
		Grid() = default;

		//Grid Constructor
		Grid(sf::Vector2<size_t>const& cellCount, sf::Vector2f const& gridPos, sf::Vector2f const& gridBorder, sf::Color const& gridColor, sf::Color const& cellColor, sf::Vector2f const& cellSize, float cellGap);

		//Draw Grid
		void drawGrid();
	};
}

#endif // !MAP_HPP