/*****************************************************************************************************************
@file         Animation.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for Animation classes & object defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Animation.hpp"

// ================================================================================
// Class: Sprite Sheet Animation Class
// ================================================================================

//Constructor
Animation::SheetAnimator::SheetAnimator(sf::Vector2i const& sheetsize, sf::Vector2i const& spritesize, float animatespeed, bool pingpong, sf::Vector2i const& start, sf::Vector2i const& end)
	:	sheetSize{ sheetsize }, spriteSize{ spritesize }, 
		animationSpeed{ animatespeed }, timer(), b_pingpong{ pingpong }, b_reverse{ false },
		startSprite{ start }, endSprite{ end }, currSprite{ startSprite } {}

//Setters
void Animation::SheetAnimator::SetSpriteSheet(sf::Vector2i const& sheetsize, sf::Vector2i const& spritesize, float animatespeed, bool pingpong, sf::Vector2i const& start, sf::Vector2i const& end) {
	sheetSize = sheetsize;
	spriteSize = spritesize;
	animationSpeed = animatespeed;
	startSprite = start;
	endSprite = end;
	b_pingpong = pingpong;
}

void Animation::SheetAnimator::resetCurrSprite() {
	currSprite = startSprite;
}

//Animators
void Animation::SheetAnimator::animateTexture(sf::Shape& obj) {
	obj.setTextureRect(sf::IntRect(currSprite, spriteSize));

	//Iterate Sprites
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

void Animation::SheetAnimator::animateTexture(sf::Sprite& obj) {

	//Set TextureRect
	obj.setTextureRect(sf::IntRect(currSprite, spriteSize));

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
