/*****************************************************************************************************************
@file         Utils.cpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This file contains the definitions of utility functions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Utils.hpp"

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