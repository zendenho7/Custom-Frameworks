/*****************************************************************************************************************
@file         Entity.hpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the header file for the entitiy classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "..\..\Header\Utility\Animation.hpp"

namespace Entity {

	//Entity Origin Positions
	enum class Origin : sf::Uint8 {
		CENTER = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOT_RIGHT,
		BOT_LEFT
	};

	//Base Entity ( To Add Functionalities To All Entity Classes )
	class base {
	private:
		//Origin Position Of Entity
		Origin originPos;

	public:
		//Constructors
		base() = default;
		base(Origin oPos) : originPos{oPos} {}

		//Set Origin Of Entity
		void setOrigin(sf::Transformable& obj, sf::Vector2f const& size);

		//Virtual Destructor
		virtual ~base() = default;
	};

	//Rect Entity
	class rect : public base {
	private:

	public:

		//Drawable
		sf::RectangleShape d_Rect;

		//Constructors
		rect() = default;
		rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};

	//Sprite Entity Derived From Rect Entity ( Rect Represents Bounding Box In Sprite )
	class sprite : public base {
	private:
		//For SpriteSheet
		sf::Vector2f spriteSize;
		sf::Vector2i spriteRowCol;
	public:
		//Drawable
		sf::Sprite d_Sprite;

		//Temporary Attached To Sprite For Testing
		Animation::SheetAnimator animate;

		//Constructors
		sprite() = default;
		sprite(sf::Texture const& tex, sf::Vector2i const& rowcolcount, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);

		void setTexture(sf::Texture const& tex, sf::Vector2i const& rowcolcount);
	};

	//Circle Entity Derived From Cirlce Entity ( Rect Represents Bounding Box In Circle )
	class circle : public base {
	private:

	public:
		//Drawable
		sf::CircleShape d_Circle;

		//Constructors
		circle() = default;
		circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);
	};
}

#endif // !ENTITY_HPP
