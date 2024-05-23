/*****************************************************************************************************************
@file         Animation.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for Animation classes & object defintions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Animation.hpp"

// ================================================================================
// Class: Base Animator
// ================================================================================
Animation::BaseAnimator::BaseAnimator()
	: animationsToComplete{ 0 }, completedAnimations{ 0 }, animationStop{ false },
	animationFinished{ false }, b_pingpong{ false }, b_reverse{ false }, animationSpeed{ 0.0f } 
{}

Animation::BaseAnimator::BaseAnimator(bool pingpong, int animationstocomplete, float animatespeed)
	: animationsToComplete{ animationstocomplete }, completedAnimations{ 0 }, animationStop{ false },
	animationFinished{ false }, b_pingpong{ pingpong }, b_reverse{ false }, animationSpeed{ animatespeed } 
{}

void Animation::BaseAnimator::initBaseAnimator(bool pingpong, int animationstocomplete, float animatespeed) {
	b_pingpong = pingpong;
	animationsToComplete = animationstocomplete;
	animationSpeed = animatespeed;
}

void Animation::BaseAnimator::animationEndChecker() {
	//Incr Completed Animations
	if (++completedAnimations >= animationsToComplete && animationsToComplete) {
		animationFinished = true;
		animationStop = true;
		animationsToComplete = completedAnimations;
	}
}

void Animation::BaseAnimator::stopAnimation() {
	animationStop = true;
}

void Animation::BaseAnimator::resumeAnimation() {
	if (!animationFinished) {
		animationStop = false;
	}
}

void Animation::BaseAnimator::restartAnimation() {
	animationStop = false;
	animationFinished = false;
	completedAnimations = 0;

	b_reverse = false;
}

void Animation::BaseAnimator::initSheetAnimatorFinished() {
	animationFinished = true;
	animationStop = true;
}

bool Animation::BaseAnimator::isAnimationFinished() const {
	return animationFinished;
}

void Animation::BaseAnimator::setPingPongAnimation(bool enable) {
	b_pingpong = enable;
}

bool Animation::BaseAnimator::getPingPongAnimation() const {
	return b_pingpong;
}

void Animation::BaseAnimator::initSheetAnimatorsToComplete(int count) {
	animationsToComplete = count;
}

int Animation::BaseAnimator::getAnimationsToComplete() {
	return animationsToComplete;
}

int Animation::BaseAnimator::getCompletedAnimations() const {
	return completedAnimations;
}

void Animation::BaseAnimator::initSheetAnimatorSpeed(float speed) {
	animationSpeed = speed;
}

float Animation::BaseAnimator::getAnimationSpeed() const {
	return animationSpeed;
}

std::string Animation::BaseAnimator::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << animationsToComplete << " " << completedAnimations << " " << animationStop << " "
		<< animationFinished << " " << b_pingpong << " " << b_reverse << " " << animationSpeed;

	return oss.str();
}

void Animation::BaseAnimator::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Output Stream From String
	iss >> animationsToComplete >> completedAnimations >> animationStop
		>> animationFinished >> b_pingpong >> b_reverse >> animationSpeed;
}

std::istringstream& Animation::BaseAnimator::deserialize(std::istringstream& stream) {
	//Output Stream From String
	stream >> animationsToComplete >> completedAnimations >> animationStop
		>> animationFinished >> b_pingpong >> b_reverse >> animationSpeed;

	return stream;
}

// ================================================================================
// Class: Sprite Sheet Animator
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

void Animation::SheetAnimator::numSpritesToAnimate(sf::Vector2u const& startIndex, sf::Vector2u const& endIndex) {
	//Calculating Num Of Sprites To Animate
	for (unsigned int i = startIndex.y; i < (sheetSize.y / spriteSize.y); i++) {
		for (unsigned int j = startIndex.x; j < (sheetSize.x / spriteSize.x); j++) {

			//Inc Num Of Sprites To Animate
			numSprites++;

			//Check If End Index Has Been Reached
			if (i == endIndex.y && j == endIndex.x) {
				return;
			}
		}
	}
}

Animation::SheetAnimator::SheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex, float animatespeed, bool pingpong, int numOfAnimations)
	:	BaseAnimator(),sheetSize{ sheetsize }, spriteSize{ spritesize }, numSprites{ 0 }, timer(),
		startSprite{ startIndex.x * spriteSize.x, startIndex.y * spriteSize.y }, endSprite{ endIndex.x * spriteSize.x, endIndex.y * spriteSize.y }, currSprite{ startSprite } 
{
	//Assert Index Out Of Range
	assert((startIndex.x < (sheetSize.x / spriteSize.x) && startIndex.y < (sheetSize.y / spriteSize.y)) && "Start Index Out Of Range!");
	assert((endIndex.x < (sheetSize.x / spriteSize.x) && endIndex.y < (sheetSize.y / spriteSize.y)) && "End Index Out Of Range!");

	//Initialize Animation Sheet Variables
	animationSpeed = animatespeed;
	animationsToComplete = numOfAnimations;
	b_pingpong = pingpong;

	//Calculate Number Of Sprites
	numSpritesToAnimate(startIndex, endIndex);
}

void Animation::SheetAnimator::initSheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex, float animatespeed, bool pingpong, int numOfAnimations) {
	//Assert Index Out Of Range
	assert((startIndex.x < (sheetSize.x / spriteSize.x) && startIndex.y < (sheetSize.y / spriteSize.y)) && "Start Index Out Of Range!");
	assert((endIndex.x < (sheetSize.x / spriteSize.x) && endIndex.y < (sheetSize.y / spriteSize.y)) && "End Index Out Of Range!");
	
	//Initialize Animation Sheet Variables
	sheetSize = sheetsize;
	spriteSize = static_cast<sf::Vector2u>(spritesize);
	animationSpeed = animatespeed;
	animationsToComplete = numOfAnimations;
	startSprite = { startIndex.x * spriteSize.x, startIndex.y* spriteSize.y };
	endSprite = { endIndex.x * spriteSize.x, endIndex.y * spriteSize.y };
	currSprite = startSprite;
	b_pingpong = pingpong;
	numSpritesToAnimate(startIndex, endIndex);
}

void Animation::SheetAnimator::restartAnimation() {
	BaseAnimator::restartAnimation();
	currSprite = startSprite;
}

void Animation::SheetAnimator::animateTexture(sf::Shape& obj) {
	//Set TextureRect
	obj.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(currSprite), static_cast<sf::Vector2i>(spriteSize)));

	//Calculate Time Before Next Animation
	float timePerAnimation{ animationSpeed / numSprites };

	//Wait For Next Iteration
	if (timer.getElapsedTime().asSeconds() >= timePerAnimation && !animationStop) {

		//Reset Timer
		timer.restart();

		//Iterate Curr Sprite
		if (!b_reverse) {
			iterateForward();
		}
		else {
			iterateBackWard();
		}

		//If End Has Been Reached
		if (currSprite == endSprite) {
			//Check If Animation Is Finished
			animationEndChecker();

			//PingPong Function Checking
			if (b_pingpong) {

				//Set Reverse Iterator To True
				b_reverse = true;
			}
			else {
				currSprite = startSprite;
			}
		}

		//If CurrSprite Is At Start
		if (currSprite == startSprite && b_reverse) {
			//Check If Animation Is Finished
			animationEndChecker();

			//Set Reverse Iterator To False
			b_reverse = false;
		}
	}
}

void Animation::SheetAnimator::animateTexture(sf::Sprite& obj) {

	//Set TextureRect
	obj.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(currSprite), static_cast<sf::Vector2i>(spriteSize)));

	//Calculate Time Before Next Animation
	float timePerAnimation{ animationSpeed / numSprites };

	//Wait For Next Iteration
	if (timer.getElapsedTime().asSeconds() >= timePerAnimation && !animationStop) {

		//Reset Timer
		timer.restart();

		//Iterate Curr Sprite
		if (!b_reverse) {
			iterateForward();
		}
		else {
			iterateBackWard();
		}

		//If End Has Been Reached
		if (currSprite == endSprite) {
			//Check If Animation Is Finished
			animationEndChecker();

			//PingPong Function Checking
			if (b_pingpong) {

				//Set Reverse Iterator To True
				b_reverse = true;
			}
			else {
				currSprite = startSprite;
			}
		}

		//If CurrSprite Is At Start
		if (currSprite == startSprite && b_reverse) {
			//Check If Animation Is Finished
			animationEndChecker();

			//Set Reverse Iterator To False
			b_reverse = false;
		}
	}
}

std::string Animation::SheetAnimator::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << BaseAnimator::serialize() << " " << sheetSize.x << " " << sheetSize.y << " "
		<< spriteSize.x << " " << spriteSize.y << " " << numSprites << " "
		<< startSprite.x << " " << startSprite.y << " " << endSprite.x << " " << endSprite.y << " "
		<< currSprite.x << " " << currSprite.y;

	return oss.str();
}

void Animation::SheetAnimator::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Output Stream From String
	BaseAnimator::deserialize(iss) >> sheetSize.x >> sheetSize.y
		>> spriteSize.x >> spriteSize.y >> numSprites
		>> startSprite.x >> startSprite.y >> endSprite.x >> endSprite.y
		>> currSprite.x >> currSprite.y;
}

std::istringstream& Animation::SheetAnimator::deserialize(std::istringstream& stream) {
	//Output Stream From String
	BaseAnimator::deserialize(stream) >> sheetSize.x >> sheetSize.y
		>> spriteSize.x >> spriteSize.y >> numSprites
		>> startSprite.x >> startSprite.y >> endSprite.x >> endSprite.y
		>> currSprite.x >> currSprite.y;

	return stream;
}

// ================================================================================
// Class: Fade Animator
// ================================================================================

Animation::FadeAnimator::FadeAnimator()
	: BaseAnimator(), startOpacity{ 0 }, endOpacity{ 255 }, currentOpacity{ 0.0f }, startMoreThanEnd{ false } 
{}

Animation::FadeAnimator::FadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed, bool pingpong, int numOfAnimations)
	: BaseAnimator(pingpong, numOfAnimations, animatespeed), startOpacity{ startingOpacity }, endOpacity{ endingOpacity }, currentOpacity{ static_cast<float>(startOpacity) }, startMoreThanEnd{ startOpacity > endOpacity }
{}

void Animation::FadeAnimator::initFadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed, bool pingpong, int numOfAnimations) {
	animationSpeed = animatespeed;
	b_pingpong = pingpong;
	animationsToComplete = numOfAnimations;
	startOpacity = startingOpacity;
	endingOpacity = endingOpacity;
	currentOpacity = static_cast<float>(startOpacity);
	startMoreThanEnd = startOpacity > endOpacity;
}

std::string Animation::FadeAnimator::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << BaseAnimator::serialize() << " " << startOpacity << " " << endOpacity << " " << currentOpacity << " " << startMoreThanEnd;

	return oss.str();
}

void Animation::FadeAnimator::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Output Stream From String
	BaseAnimator::deserialize(iss) >> startOpacity >> endOpacity >> currentOpacity >> startMoreThanEnd;
}

std::istringstream& Animation::FadeAnimator::deserialize(std::istringstream& stream) {
	//Output Stream From String
	BaseAnimator::deserialize(stream) >> startOpacity >> endOpacity >> currentOpacity >> startMoreThanEnd;

	return stream;
}
