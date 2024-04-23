/*****************************************************************************************************************
@file         Utils.hpp
@project      Pathfinding Algorithms
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

// ================================================================================
// EXTERNALS
// ================================================================================

extern Systems::EventHandler* exEvents;
extern Systems::FrameTime* exTime;
extern Load::Assets* exAssets;

// ================================================================================
// Namspace: Entities
// ================================================================================

namespace Entity {

	//Entity Origin Positions
	enum class Origin : sf::Uint8 {
		CENTER = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOT_RIGHT,
		BOT_LEFT
	};

	//Rect Entity
	class rect {
	private:
		Origin originPos;

	public:
		sf::RectangleShape drawableRect;

		rect() = default;
		rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		void setOrigin(sf::Transformable& obj, sf::Vector2f const& size);
	};

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

	class circle {

	};
}

// ================================================================================
// EXTERALS
// ================================================================================

#endif // !UTILS_HPP
