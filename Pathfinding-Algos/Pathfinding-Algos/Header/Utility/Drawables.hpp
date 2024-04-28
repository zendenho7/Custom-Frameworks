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
	void setOrigin(sf::Transformable& drawables, sf::Vector2f const& size, Origin oPos = Origin::CENTER);

	//Rounded Rect Custom Convex Shape
	class D_RoundedRectangle : public sf::ConvexShape {
	private:
		//Rounded Rect Constants
		const int	RECT_EDGES{ 4 };
		const int	ROUNDING_POINTS_PER_EDGE{ 10 };
		const float	FULL_RAD_ROTATION{ static_cast<float>(2.0f * M_PI) };

		//Vertex Manager
		sf::Vector2f rectVertex[4];

		//Rounding
		float cornerRounding;

		//Update Points Positioning
		void setPoints();

	protected:

	public:
		D_RoundedRectangle() = default;
		D_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Get Rounding
		void setCornerRounding(float rounding);
		float getCornerRounding() const;
	};

	class D_Rectangle : public sf::RectangleShape {
	private:

	public:
		D_Rectangle() = default;
		D_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};

	class D_Circle : public sf::CircleShape {
	private:

	public:
		D_Circle() = default;
		D_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};

	class D_Sprite : public sf::Sprite {
	private:

	public:
		D_Sprite() = default;
		D_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);
	};
}

#endif // !DRAWABLES_HPP
