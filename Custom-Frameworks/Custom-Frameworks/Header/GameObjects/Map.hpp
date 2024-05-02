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
		Cell(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding);
	};
	
	class Grid {
	private:
		//Array Of Cells
		std::vector<std::vector<Cell>> gridArray;

	public:
		//Ddefault Grid Constructor
		Grid() = default;

		//Grid Constructor
		Grid(sf::Vector2<size_t>const& gridCount, sf::Vector2f const& gridPos, sf::Color const& cellColor, sf::Vector2f const& cellSize, float cellRounding = 0.0f);
	};
}

#endif // !MAP_HPP