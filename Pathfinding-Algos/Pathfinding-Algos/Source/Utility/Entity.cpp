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
// Class: Rect Entity Member Functions
// ================================================================================

Entity::rect::rect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
	: d_Rect(size), originPos{ oPos }
{
	//Set Entity Components
	d_Rect.setPosition(pos);
	d_Rect.setRotation(rotation);
	d_Rect.setFillColor(color);

	//Center Origin Of Entity
	setOrigin(d_Rect, d_Rect.getLocalBounds().getSize());
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

Entity::sprite::sprite(sf::Texture const& tex, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
	: rect(sf::Color::White, size, pos, rotation, oPos), d_Sprite(tex)
{
	//Set Entity Components
	d_Sprite.setScale(size.x / d_Sprite.getLocalBounds().getSize().x, size.y / d_Sprite.getLocalBounds().getSize().y);
	d_Sprite.setPosition(pos);
	d_Sprite.setRotation(rotation);
	d_Sprite.setColor({ 255, 255, 255, opacity });

	//Set Origin
	setOrigin(d_Sprite, d_Sprite.getLocalBounds().getSize());
}

void Entity::sprite::updateBounding() {
	d_Rect.setPosition(d_Sprite.getPosition());
	d_Rect.setRotation(d_Sprite.getRotation());
	d_Rect.setScale(d_Sprite.getLocalBounds().getSize().x * d_Sprite.getScale().x / d_Rect.getSize().x, d_Sprite.getLocalBounds().getSize().y * d_Sprite.getScale().y / d_Rect.getSize().y);
}

// ================================================================================
// Class: Circle Entity Member Functions
// ================================================================================

Entity::circle::circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
	: rect(sf::Color::White, {2 * radius, 2 * radius }, pos, rotation, oPos), d_Circle(radius)
{
	//Set Entity Components
	d_Circle.setPosition(pos);
	d_Circle.setRotation(rotation);
	d_Circle.setFillColor(color);

	//Set Origin
	setOrigin(d_Circle, d_Circle.getLocalBounds().getSize());
}

void Entity::circle::updateBounding() {
	d_Rect.setPosition(d_Circle.getPosition());
	d_Rect.setRotation(d_Circle.getRotation());
	d_Rect.setScale(d_Circle.getScale());
}
