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
		//Origin Position Of Entity
		Origin originPos;

	public:
		//Drawable
		sf::RectangleShape d_Rect;

		//Constructors
		rect() = default;
		rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Set Origin Of Entity
		void setOrigin(sf::Transformable& obj, sf::Vector2f const& size);
	};

	//Sprite Entity Derived From Rect Entity ( Rect Represents Bounding Box In Sprite )
	class sprite : public rect {
	private:

	public:
		//Drawable
		sf::Sprite d_Sprite;

		//Constructors
		sprite() = default;
		sprite(sf::Texture const& tex, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);

		//Update Bounding Box If Needed For Display Purposes
		void updateBounding();
	};

	//Circle Entity Derived From Cirlce Entity ( Rect Represents Bounding Box In Circle )
	class circle : public rect {
	private:

	public:
		//Drawable
		sf::CircleShape d_Circle;

		//Constructors
		circle() = default;
		circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Update Bounding Box If Needed For Display Purposes
		void updateBounding();
	};
}

#endif // !ENTITY_HPP
