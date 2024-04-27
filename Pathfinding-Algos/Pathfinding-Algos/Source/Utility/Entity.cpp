/*****************************************************************************************************************
@file         Entity.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for entity classes & object defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Entity.hpp"

// ================================================================================
// Class: Base Entity Member Function
// ================================================================================

void Entity::base::setOrigin(sf::Transformable& obj, sf::Vector2f const& size) {

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
// Class: Rect Entity Member Functions
// ================================================================================

Entity::rect::rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
	: base{ oPos }, d_Rect(size)
{
	//Set Entity Components
	d_Rect.setPosition(pos);
	d_Rect.setRotation(rotation);
	d_Rect.setFillColor(color);

	//Center Origin Of Entity
	setOrigin(d_Rect, d_Rect.getLocalBounds().getSize());
}

// ================================================================================
// Class: Sprite Entity Member Functions
// ================================================================================

Entity::sprite::sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
	: base(oPos), d_Sprite(tex, spritePos)
{
	//Set Entity Components
	d_Sprite.setScale(size.x / (d_Sprite.getLocalBounds().getSize().x), size.y / (d_Sprite.getLocalBounds().getSize().y));
	d_Sprite.setPosition(pos);
	d_Sprite.setRotation(rotation);
	d_Sprite.setColor({ 255, 255, 255, opacity });

	//Set Origin
	setOrigin(d_Sprite, d_Sprite.getLocalBounds().getSize());
}

void Entity::sprite::setTexture(sf::Texture const& tex, sf::IntRect const& spritePos) {
	d_Sprite.setTexture(tex);
	d_Sprite.setTextureRect(spritePos);
}

// ================================================================================
// Class: Circle Entity Member Functions
// ================================================================================

Entity::circle::circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
	: base(oPos), d_Circle(radius)
{
	//Set Entity Components
	d_Circle.setPosition(pos);
	d_Circle.setRotation(rotation);
	d_Circle.setFillColor(color);

	//Set Origin
	setOrigin(d_Circle, d_Circle.getLocalBounds().getSize());
}
