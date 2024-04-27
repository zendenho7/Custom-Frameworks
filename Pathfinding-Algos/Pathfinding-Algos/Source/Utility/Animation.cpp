/*****************************************************************************************************************
@file         Animation.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for Animation classes & object defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Animation.hpp"

// ================================================================================
// Class: Sprite Sheet Constructor
// ================================================================================

Animation::SheetAnimator::SheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, float animatespeed, bool pingpong, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex)
	:	sheetSize{ sheetsize }, spriteSize{ spritesize }, 
		animationSpeed{ animatespeed }, timer(), b_pingpong{ pingpong }, b_reverse{ false },
		startSprite{ startIndex.x * spriteSize.x, startIndex.y * spriteSize.y }, endSprite{ endIndex.x * spriteSize.x, endIndex.y * spriteSize.y }, currSprite{ startSprite } {}

// ================================================================================
// Class: Sprite Sheet Setters & Resetters
// ================================================================================

void Animation::SheetAnimator::SetSpriteSheet(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, float animatespeed, bool pingpong, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex) {
	sheetSize = sheetsize;
	spriteSize = static_cast<sf::Vector2u>(spritesize);
	animationSpeed = animatespeed;
	startSprite = { startIndex.x * spriteSize.x, startIndex.y* spriteSize.y };
	endSprite = { endIndex.x * spriteSize.x, endIndex.y * spriteSize.y };
	b_pingpong = pingpong;
}

void Animation::SheetAnimator::resetCurrSprite() {
	currSprite = startSprite;
}

// ================================================================================
// Class: Sprite Sheet Iterator
// ================================================================================
void Animation::SheetAnimator::iterateForward() {
	//Iterate Sprites Forward
	if (currSprite.x < sheetSize.x - spriteSize.x) {
		//Increment X
		currSprite.x += spriteSize.x;
	}
	else {
		//Reset X To Left Side Of Sheet
		currSprite.x = 0;

		//Increment Y Or Reset Y To Top Of Sheet
		if (currSprite.y < sheetSize.y - spriteSize.y) {
			currSprite.y += spriteSize.y;
		}
		else {
			currSprite.y = 0;
		}
	}
}

void Animation::SheetAnimator::iterateBackWard() {
	//Iterate Sprites Backward
	if (currSprite.x > 0) {
		//Increment X
		currSprite.x -= spriteSize.x;
	}
	else {
		//Reset X To Left Side Of Sheet
		currSprite.x = sheetSize.x - spriteSize.x;

		//Increment Y Or Reset Y To Top Of Sheet
		if (currSprite.y > 0) {
			currSprite.y -= spriteSize.y;
		}
		else {
			currSprite.y = sheetSize.y - spriteSize.y;
		}
	}
}

// ================================================================================
// Class: Sprite Sheet Animator
// ================================================================================
void Animation::SheetAnimator::animateTexture(sf::Shape& obj) {
	//Set TextureRect
	obj.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(currSprite), static_cast<sf::Vector2i>(spriteSize)));

	//Wait For Next Iteration
	if (timer.getElapsedTime().asSeconds() >= animationSpeed) {

		//Iterate Curr Sprite
		if (!b_reverse) {
			iterateForward();
		}
		else {
			iterateBackWard();
		}

		//If End Has Been Reached
		if (currSprite == endSprite) {

			if (b_pingpong) {
				b_reverse = true;
			}
			else {
				currSprite = startSprite;
			}
		}

		//If CurrSprite Is At Start
		if (currSprite == startSprite) {
			b_reverse = false;
		}

		//Reset Timer
		timer.restart();
	}
}

void Animation::SheetAnimator::animateTexture(sf::Sprite& obj) {

	//Set TextureRect
	obj.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(currSprite), static_cast<sf::Vector2i>(spriteSize)));

	//Wait For Next Iteration
	if (timer.getElapsedTime().asSeconds() >= animationSpeed) {

		//Iterate Curr Sprite
		if (!b_reverse) {
			iterateForward();
		}
		else {
			iterateBackWard();
		}

		//If End Has Been Reached
		if (currSprite == endSprite) {

			if (b_pingpong) {
				b_reverse = true;
			}
			else {
				currSprite = startSprite;
			}
		}

		//If CurrSprite Is At Start
		if (currSprite == startSprite) {
			b_reverse = false;
		}

		//Reset Timer
		timer.restart();
	}
}
