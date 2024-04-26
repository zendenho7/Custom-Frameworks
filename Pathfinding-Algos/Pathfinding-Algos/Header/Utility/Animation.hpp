/*****************************************************************************************************************
@file         Animation.hpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the header file for Animation classes & object
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

namespace Animation {
	//Animation Constants
	const float ANIMATE_SPEED = 0.1f;


	//SheetAnimation Class ( Only For Uniform Sprite Spritesheet )
	//Animation Goes From Left To Right & Top To Bottom
	class SheetAnimator {
	private:
		//Sprite Sheet Sizes
		sf::Vector2i sheetSize;
		sf::Vector2i spriteSize;

		//Speed Of Animation
		float animationSpeed;
		sf::Clock timer;

		//PingPong Animation
		bool b_pingpong;
		bool b_reverse;

		//Sprite Positions ( Pos Based Off Of Top Left Coordinate )
		sf::Vector2i startSprite;
		sf::Vector2i endSprite;

		//Current Sprite Position
		sf::Vector2i currSprite;

		//Sheet Iterator Function
		void iterateForward();
		void iterateBackWard();
	public:

		//Constructors
		SheetAnimator() : animationSpeed{ 0.0f }, b_pingpong{ false }, b_reverse{ false }{}
		SheetAnimator(sf::Vector2i const& sheetsize, sf::Vector2i const& spritesize, float animatespeed = ANIMATE_SPEED, bool pingpong = false, sf::Vector2i const& start = sf::Vector2i(0, 0), sf::Vector2i const& end = sf::Vector2i(0, 0));

		//SpriteSheet Setter
		void SetSpriteSheet(sf::Vector2i const& sheetsize, sf::Vector2i const& spritesize, float animatespeed = ANIMATE_SPEED, bool pingpong = false, sf::Vector2i const& start = sf::Vector2i(0, 0), sf::Vector2i const& end = sf::Vector2i(0, 0));
		void resetCurrSprite();

		//Animte Sprite Sheet Function Call ( If Start == End, Animation Will Go Through The Whole Spritesheet )
		void animateTexture(sf::Shape& obj);
		void animateTexture(sf::Sprite& obj);
	};
}

#endif // !ANIMATION_HPP
