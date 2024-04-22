/*****************************************************************************************************************
@file         Utils.cpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This file contains the definitions of utility functions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Utils.hpp"

// ================================================================================
// Class: Rect Entity Member Functions
// ================================================================================

Entity::rect::rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
	: drawableRect(size), originPos{ oPos }
{
	//Set Entity Components
	drawableRect.setPosition(pos);
	drawableRect.setRotation(rotation);
	drawableRect.setFillColor(color);

	//Center Origin Of Entity
	setOrigin(drawableRect, { drawableRect.getSize().x, drawableRect.getSize().y });
}

void Entity::rect::setOrigin(sf::Transformable& obj, sf::Vector2f const& size) {

	//Switch Cases For Origin Setting
	switch (originPos) {
	case Origin::CENTER:
		obj.setOrigin(size.x / 2, size.y / 2);
		break;
	case Origin::TOP_LEFT:
		obj.setOrigin(0.0f, 0.0f);
		break;
	case Origin::TOP_RIGHT:
		obj.setOrigin(size.x, 0.0f);
		break;
	case Origin::BOT_RIGHT:
		obj.setOrigin(size.x, size.y);
		break;
	case Origin::BOT_LEFT:
		obj.setOrigin(0.0f, size.y);
		break;
	default:
		break;
	}
}

// ================================================================================
// Class: Sprite Entity Member Functions
// ================================================================================

Entity::sprite::sprite(sf::Texture const& tex, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, bool centerOrigin)
: drawable(tex), centerOrigin{centerOrigin}, bound()
{
	//Set Entity Components
	drawable.setScale(size.x / drawable.getTexture()->getSize().x, size.y / drawable.getTexture()->getSize().y);
	drawable.setPosition(pos);
	drawable.setRotation(rotation);
	drawable.setColor({ 255, 255, 255, opacity });

	//Set Bounding Rect
	bound.setSize({ drawable.getScale().x * drawable.getTexture()->getSize().x, drawable.getScale().y * drawable.getTexture()->getSize().y });
	bound.setPosition(drawable.getPosition());
	bound.setRotation(drawable.getRotation());
	drawable.setColor(drawable.getColor());

	//Center Origin Of Entity
	if (centerOrigin) {
		drawable.setOrigin((static_cast<float>(drawable.getTexture()->getSize().x)) / 2, (static_cast<float>(drawable.getTexture()->getSize().y)) / 2);
		bound.setOrigin(bound.getSize().x / 2, bound.getSize().y / 2);
	}
}