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
	// ================================================================================
	// CONSTANTS
	// ================================================================================
	const float ANIMATE_SPEED = 0.1f;

	// ================================================================================
	// Class: Sprite Sheet Animation Class ( Top Left To Bot Right Iteration )
	// ================================================================================
	class SheetAnimator {
	private:
		//Sprite Sheet Sizes
		sf::Vector2u sheetSize;
		sf::Vector2u spriteSize;

		//Speed Of Animation
		float animationSpeed;
		sf::Clock timer;

		//PingPong Animation
		bool b_pingpong;
		bool b_reverse;

		//Sprite Position ( Based On Top Left Corner Of Sprite )
		sf::Vector2u startSprite;
		sf::Vector2u endSprite;

		//Current Sprite Position
		sf::Vector2u currSprite;

		//Sheet Iterator Function
		void iterateForward();
		void iterateBackWard();
	public:

		//Constructors
		SheetAnimator() : animationSpeed{ 0.0f }, b_pingpong{ false }, b_reverse{ false }{}

		/// <summary>
		/// Arguement Constructor For Sprite Sheet Animation
		/// </summary>
		/// <param name="sheetsize">Size Of Sprite Sheet</param>
		/// <param name="spritesize">Size Of Sprite Within Spritesheet ( Applies Only To Same Size Sprite )</param>
		/// <param name="animatespeed">Speed Of Animation</param>
		/// <param name="pingpong">PingPong Function Defaulted To False</param>
		/// <param name="startIndex">Starting Index Of Iterator</param>
		/// <param name="endIndex">Ending Index Of Iterator</param>
		SheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, float animatespeed = ANIMATE_SPEED, bool pingpong = false, sf::Vector2u const& startIndex = sf::Vector2u(0, 0), sf::Vector2u const& endIndex = sf::Vector2u(0, 0));

		/// <summary>
		/// SpriteSheet Animation Setter
		/// </summary>
		/// <param name="sheetsize">Size Of Sprite Sheet</param>
		/// <param name="spritesize">Size Of Sprite Within Spritesheet ( Applies Only To Same Size Sprite )</param>
		/// <param name="animatespeed">Speed Of Animation</param>
		/// <param name="pingpong">PingPong Function Defaulted To False</param>
		/// <param name="startIndex">Starting Index Of Iterator</param>
		/// <param name="endIndex">Ending Index Of Iterator</param>
		void SetSpriteSheet(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, float animatespeed = ANIMATE_SPEED, bool pingpong = false, sf::Vector2u const& startIndex = sf::Vector2u(0, 0), sf::Vector2u const& endIndex = sf::Vector2u(0, 0));
		void resetCurrSprite();

		//Animte Sprite Sheet Function Call ( If Start == End, Animation Will Go Through The Whole Spritesheet )
		void animateTexture(sf::Shape& obj);
		void animateTexture(sf::Sprite& obj);
	};
}

#endif // !ANIMATION_HPP
