/*****************************************************************************************************************
@file         Drawables.hpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the header file for the drawables helper functions declarations
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef DRAWABLES_HPP
#define DRAWABLES_HPP

namespace Drawables {

	//Drawables Origin Positions
	enum class Origin : sf::Uint8 {
		CENTER = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOT_RIGHT,
		BOT_LEFT
	};

	//Set Origin Of Drawables
	void setOrigin(sf::Transformable& drawables, sf::Vector2f const& size, Origin oPos);

	//Construct Drawable Shapes
	void initRectShape(sf::RectangleShape& drawables, sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

	void initCircleShape(sf::CircleShape& drawables, sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

	//Construct Drawable Sprites
	void initSprite(sf::Sprite& drawables, sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);
}

#endif // !DRAWABLES_HPP
