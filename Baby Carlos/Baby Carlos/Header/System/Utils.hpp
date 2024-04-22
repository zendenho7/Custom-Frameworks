/*****************************************************************************************************************
@file         Utils.hpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This is the header files for this application's utility functions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\System\Load.hpp"

#ifndef UTILS_HPP
#define UTILS_HPP

namespace Entity {
	class sprite {
	private:
		//Origin Management Flag ( Only For Centering Origin )
		bool centerOrigin;
		
	public:
		//Drawable
		sf::Sprite drawable;

		//Bound Rendering
		sf::RectangleShape bound;

		sprite() = default;
		sprite(sf::Texture const& tex, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, bool centerOrigin = true);
	};

	class rect {

	};

	class circle {

	};
}

// ================================================================================
// EXTERALS
// ================================================================================

#endif // !UTILS_HPP
