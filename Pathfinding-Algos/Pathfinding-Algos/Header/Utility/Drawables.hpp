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

	// ================================================================================
	// Constants
	// ================================================================================
	const sf::Uint8  DEF_CHAR_SIZE{ 72 };

	// ================================================================================
	// Enums: Defined Origin Types
	// ================================================================================
	enum class Origin : sf::Uint8 {
		CENTER = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOT_RIGHT,
		BOT_LEFT
	};

	// ================================================================================
	// Class: Template Base Drawable
	// ================================================================================
	template<typename T>
	class D_Base : public T {
	private:
		sf::Vector2f fixedScale;

	public:
		//Constructors
		D_Base() : fixedScale{ 1.0f, 1.0f } {}

		//Custom Member Functions
		void Custom_SetOrigin(Origin oPos = Origin::CENTER) {
			//Size Of Object
			sf::Vector2f size{ T::getLocalBounds().getSize() };

			//Switch Cases For Origin Setting
			switch (oPos) {
			case Origin::CENTER:
				T::setOrigin(size.x / 2, size.y / 2);
				break;
			case Origin::TOP_LEFT:
				T::setOrigin(0.0f, 0.0f);
				break;
			case Origin::TOP_RIGHT:
				T::setOrigin(size.x, 0.0f);
				break;
			case Origin::BOT_RIGHT:
				T::setOrigin(size.x, size.y);
				break;
			case Origin::BOT_LEFT:
				T::setOrigin(0.0f, size.y);
				break;
			default:
				break;
			}
		}

		//Set Fixed Scale ( For Size Manipulation )
		void Custom_SetFixedScale() {
			fixedScale = T::getScale();
		}

		//Get Fixed Scale
		sf::Vector2f const& Custom_GetFixedScale() const {
			return fixedScale;
		}
	};

	// ================================================================================
	// Class: Drawable Text
	// ================================================================================

	class D_Text : public D_Base<sf::Text> {
	private:

	public:
		//Constructors
		D_Text() = default;
		D_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize = DEF_CHAR_SIZE, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		/// <summary>
		/// To Be Called Only After Setting Position
		/// </summary>
		void Custom_OffsetToCenter();
	};

	// ================================================================================
	// Class: Drawable Rounded Rectangle
	// ================================================================================
	class D_RoundedRectangle : public D_Base<sf::ConvexShape> {
	private:
		//Rounded Rect Constants
		const int	RECT_EDGES{ 4 };
		const int	ROUNDING_POINTS_PER_EDGE{ 10 };

		//Vertex Manager
		sf::Vector2f rectVertex[4];

		//Rounding
		float cornerRounding;

		//Update Points Positioning
		void setPoints();

	public:
		//Constructors
		D_RoundedRectangle() = default;
		D_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Get Rounding
		void setCornerRounding(float rounding);
		float getCornerRounding() const;
	};

	// ================================================================================
	// Class: Drawable Rectangle
	// ================================================================================
	class D_Rectangle : public D_Base<sf::RectangleShape> {
	private:

	public:
		//Constructors
		D_Rectangle() = default;
		D_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};

	// ================================================================================
	// Class: Drawable Circle
	// ================================================================================
	class D_Circle : public D_Base<sf::CircleShape> {
	private:

	public:
		//Constructors
		D_Circle() = default;
		D_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};

	// ================================================================================
	// Class: Drawable Sprite
	// ================================================================================	
	class D_Sprite : public D_Base<sf::Sprite> {
	private:

	public:
		//Constructors
		D_Sprite() = default;
		D_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);
	};
}

#endif // !DRAWABLES_HPP
