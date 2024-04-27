/*****************************************************************************************************************
@file         Drawables.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for drawables helper function defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Drawables.hpp"

// ================================================================================
// Transformable Origin Setter
// ================================================================================

void Drawables::setOrigin(sf::Transformable& drawables, sf::Vector2f const& size, Origin oPos) {

	//Switch Cases For Origin Setting
	switch (oPos) {
	case Origin::CENTER:
		drawables.setOrigin(size.x / 2, size.y / 2);
		break;
	case Origin::TOP_LEFT:
		drawables.setOrigin(0.0f, 0.0f);
		break;
	case Origin::TOP_RIGHT:
		drawables.setOrigin(size.x, 0.0f);
		break;
	case Origin::BOT_RIGHT:
		drawables.setOrigin(size.x, size.y);
		break;
	case Origin::BOT_LEFT:
		drawables.setOrigin(0.0f, size.y);
		break;
	default:
		break;
	}
}

// ================================================================================
// Rectangle Shape Initializer
// ================================================================================

void Drawables::initRectShape(sf::RectangleShape& drawables, sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	drawables.setSize(size);
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setFillColor(color);

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}

// ================================================================================
// Circle Shape Initializer
// ================================================================================

void Drawables::initCircleShape(sf::CircleShape& drawables, sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	drawables.setRadius(radius);
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setFillColor(color);

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}

// ================================================================================
// Sprite Initializer
// ================================================================================

void Drawables::initSprite(sf::Sprite& drawables, sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
{
	//Set Drawables Components
	drawables.setTexture(tex);
	drawables.setTextureRect(spritePos);
	drawables.setScale(size.x / (drawables.getLocalBounds().getSize().x), size.y / (drawables.getLocalBounds().getSize().y));
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setColor({ 255, 255, 255, opacity });

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}
