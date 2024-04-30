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

#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Utils.hpp"

namespace Animation {
	// ================================================================================
	// CONSTANTS
	// ================================================================================
	const float ANIMATE_SPEED = 2.0f;
	const float FADE_SPEED = 2.0f;

	// ================================================================================
	// Class: Sprite Sheet Animation Class ( Top Left To Bot Right Iteration )
	// ================================================================================

	class BaseAnimator {
	protected:
		//Animation Tracker ( From Start To End )
		int animationsToComplete;
		int completedAnimations;
		bool animationStop;
		bool animationFinished;

		//PingPong Animation
		bool b_pingpong;
		bool b_reverse;

		//Check If Animation Ends
		void animationEndChecker();

	public:
		//Stop Animation
		virtual void stopAnimation();

		//Resume Animation
		virtual void resumeAnimation();

		//Restart Animation ( Can Only Be Called If Animation Paused Abruptly )
		virtual void restartAnimation();

		//Return If Animation Has Stopped
		bool isAnimationFinished();

		BaseAnimator() : animationsToComplete { 0 }, completedAnimations{ 0 }, animationStop{ false }, animationFinished{ false }, b_pingpong{ false }, b_reverse{ false } {}
	};

	// ================================================================================
	// Class: Sprite Sheet Animation Class ( Top Left To Bot Right Iteration )
	// ================================================================================
	class SheetAnimator : public BaseAnimator {
	private:
		//Sprite Sheet Sizes
		sf::Vector2u sheetSize;
		sf::Vector2u spriteSize;
		unsigned int numSprites;

		//Speed Of Animation From Start To End
		float animationSpeed;
		sf::Clock timer;

		//Sprite Index ( Based On Top Left Corner Of Sprite )
		sf::Vector2u startSprite;
		sf::Vector2u endSprite;

		//Current Sprite Index
		sf::Vector2u currSprite;

		//Sheet Iterator Function
		void iterateForward();
		void iterateBackWard();

		//Calculate Number Of Sprites To Animate
		void numSpritesToAnimate(sf::Vector2u const& startIndex, sf::Vector2u const& endIndex);
	public:

		//Default Constructor
		SheetAnimator() : BaseAnimator(), numSprites{ 0 }, animationSpeed{ 0.0f } {}

		/// <summary>
		/// Constructor For Sprite Sheet Animation
		/// Note:
		/// If Start & End Index Are The Same, Whole SpriteSheet Will Be Iterated Through
		/// </summary>
		/// <param name="sheetsize">: Size Of Sprite Sheet</param>
		/// <param name="spritesize">: Size Of Sprite Within Spritesheet ( Applies Only To Same Size Sprite )</param>
		/// <param name="startIndex">: Starting Index Of Iterator</param>
		/// <param name="endIndex">: Ending Index Of Iterator</param>
		/// <param name="animatespeed">: Speed Of Animation From Start To End</param>
		/// <param name="pingpong">: PingPong Animation ( Start To End, End To Start )</param>
		/// <param name="numOfAnimations">: Number Of Recurring Animations Before Stopping ( 0 = Infinite )</param>
		SheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex, float animatespeed = ANIMATE_SPEED, bool pingpong = false, int numOfAnimations = 0);

		/// <summary>
		/// SpriteSheet Animation Setter
		/// Note:
		/// If Start & End Index Are The Same, Whole SpriteSheet Will Be Iterated Through
		/// </summary>
		/// <param name="sheetsize">: Size Of Sprite Sheet</param>
		/// <param name="spritesize">: Size Of Sprite Within Spritesheet ( Applies Only To Same Size Sprite )</param>
		/// <param name="startIndex">: Starting Index Of Iterator</param>
		/// <param name="endIndex">: Ending Index Of Iterator</param>
		/// <param name="animatespeed">: Speed Of Animation From Start To End</param>
		/// <param name="pingpong">: PingPong Animation ( Start To End, End To Start )</param>
		/// <param name="numOfAnimations">: Number Of Recurring Animations Before Stopping ( 0 = Infinite )</param>
		void setAnimation(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex, float animatespeed = ANIMATE_SPEED, bool pingpong = false, int numOfAnimations = 0);

		//Override Restart Animation From Base Animator
		void restartAnimation() override;

		//Animte Sprite Sheet Function Call ( If Start == End, Animation Will Go Through The Whole Spritesheet )
		void animateTexture(sf::Shape& obj);
		void animateTexture(sf::Sprite& obj);
	};

	// ================================================================================
	// Class: Fade Animation Class
	// ================================================================================

	class FadeAnimator : public BaseAnimator {
	private:
		//Speed Of Fade From Start To End
		float fadeSpeed;

		//Start & End Opacity
		sf::Uint8 startOpacity;
		sf::Uint8 endOpacity;
		float currentOpacity;

		//Bool For Start To End
		bool startMoreThanEnd;

	public:
		//Default Constructor
		FadeAnimator() 
			: BaseAnimator(), fadeSpeed{ 0.0f }, startOpacity{ 0 }, endOpacity{ 255 }, currentOpacity{ 0.0f }, startMoreThanEnd { false } {};

		//Fade Animator Constructor
		FadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed = FADE_SPEED, bool pingpong = false, int numOfAnimations = 0)
			: BaseAnimator(), fadeSpeed{ animatespeed }, startOpacity{ startingOpacity }, endOpacity{ endingOpacity }, currentOpacity{ static_cast<float>(startOpacity) }, startMoreThanEnd { startOpacity > endOpacity }
		{
			b_pingpong = pingpong;
			animationsToComplete = numOfAnimations;
		}

		//Set Fade Animator
		void setFadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed = FADE_SPEED, bool pingpong = false , int numOfAnimations = 0) {
			fadeSpeed = animatespeed;
			b_pingpong = pingpong;
			animationsToComplete = numOfAnimations;
			startOpacity = startingOpacity;
			endingOpacity = endingOpacity;
			currentOpacity = static_cast<float>(startOpacity);
			startMoreThanEnd = startOpacity > endOpacity;
		}

		//Template Defintion
		template<typename T>
		void fadeDrawable(Drawables::D_Base<T>& obj) {

			//Opacity Increment
			float opacityIncr { std::abs(endOpacity - startOpacity) / (fadeSpeed * exTime->getFrameRate()) };

			if (!animationStop) {
				//Iterator
				if (!b_reverse) {
					currentOpacity += startMoreThanEnd ? -opacityIncr : opacityIncr;
					obj.Custom_SetOpacity(static_cast<sf::Uint8>(std::clamp(currentOpacity, static_cast<float>(std::min(startOpacity, endOpacity)), static_cast<float>(std::max(startOpacity, endOpacity)))));
				}
				else {
					currentOpacity += startMoreThanEnd ? opacityIncr : -opacityIncr;
					obj.Custom_SetOpacity(static_cast<sf::Uint8>(std::clamp(currentOpacity, static_cast<float>(std::min(startOpacity, endOpacity)), static_cast<float>(std::max(startOpacity, endOpacity)))));
				}

				//Ends Checker
				if (!startMoreThanEnd) {
					if (currentOpacity >= endOpacity) {
						if (b_pingpong) {
							//Check If Animation Is Finished
							animationEndChecker();

							b_reverse = true;
						}
						else {
							currentOpacity = static_cast<float>(startOpacity);
							obj.Custom_SetOpacity(startOpacity);
						}
					}

					if (currentOpacity <= startOpacity) {
						//Check If Animation Is Finished
						animationEndChecker();

						b_reverse = false;
					}
				}
				else {
					if (currentOpacity <= endOpacity) {
						if (b_pingpong) {
							//Check If Animation Is Finished
							animationEndChecker();

							b_reverse = true;
						}
						else {
							currentOpacity = static_cast<float>(startOpacity);
							obj.Custom_SetOpacity(startOpacity);
						}
					}

					if (currentOpacity >= startOpacity) {
						//Check If Animation Is Finished
						animationEndChecker();

						b_reverse = false;
					}
				}
			}
		}
	};
}

#endif // !ANIMATION_HPP
