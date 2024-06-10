/*****************************************************************************************************************
@file         Animation.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file for Animation classes & object

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
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
	// Class: Base Animator Class
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

		//Animation Speed
		float animationSpeed;

		//Check If Animation Ends
		void animationEndChecker();

	protected:
		//Default Constructor
		BaseAnimator();

		//Base Animator Constructor
		BaseAnimator(bool pingpong, int animationstocomplete, float animatespeed);

		//Default Copy Constructor
		BaseAnimator(BaseAnimator const& copy) = default;

		//Remove Copy Assignment
		BaseAnimator& operator=(BaseAnimator const& copy) = delete;

		//Init Base Animator
		void initBaseAnimator(bool pingpong, int animationstocomplete, float animatespeed);

	public:

		//Stop Animation
		virtual void stopAnimation();

		//Resume Animation
		virtual void resumeAnimation();

		//Restart Animation ( Can Only Be Called If Animation Paused Abruptly )
		virtual void restartAnimation();

		//Set Animation Finished
		void initSheetAnimatorFinished();

		//Return If Animation Has Stopped
		bool isAnimationFinished() const;

		//Set PingPong Animation To Enable Or Disable
		void setPingPongAnimation(bool enable);

		//Get PingPong Animation Enable Or Disable
		bool getPingPongAnimation() const;

		//Set Animations To Complete Count
		void initSheetAnimatorsToComplete(int count);

		//Get Animations To Complete Count
		int getAnimationsToComplete();

		//Get Completed Animations Count
		int getCompletedAnimations() const;

		//Set Speed Of Animation
		void initSheetAnimatorSpeed(float speed);

		//Get Speed Of Animation
		float getAnimationSpeed() const;

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
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

		//Timer For Calculating Animation Speed
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
		SheetAnimator() : BaseAnimator(), numSprites{ 0 } {}

		//Default Copy Constructor
		SheetAnimator(SheetAnimator const& copy) = default;

		//Default Copy Assignment
		SheetAnimator& operator=(SheetAnimator const& copy) = default;

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
		void initSheetAnimator(sf::Vector2u const& sheetsize, sf::Vector2i const& spritesize, sf::Vector2u const& startIndex, sf::Vector2u const& endIndex, float animatespeed = ANIMATE_SPEED, bool pingpong = false, int numOfAnimations = 0);

		//Override Restart Animation From Base Animator
		void restartAnimation() override;

		//Animte Sprite Sheet Function Call ( If Start == End, Animation Will Go Through The Whole Spritesheet )
		void animateTexture(sf::Shape& obj);
		void animateTexture(sf::Sprite& obj);

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
	};

	// ================================================================================
	// Class: Fade Animation Class ( Defined Here Due To Template Function )
	// ================================================================================

	class FadeAnimator : public BaseAnimator {
	private:

		//Start & End Opacity
		sf::Uint8 startOpacity;
		sf::Uint8 endOpacity;
		float currentOpacity;

		//Bool For Start To End
		bool startMoreThanEnd;

	public:
		//Default Constructor
		FadeAnimator();

		//Default Copy Constructor
		FadeAnimator(FadeAnimator const& copy) = default;

		//Default Copy Assignment
		FadeAnimator& operator=(FadeAnimator const& copy) = default;

		/// <summary>
		/// Constructor For Fade Animation
		/// </summary>
		/// <param name="startingOpacity">: Starting Opacity</param>
		/// <param name="endingOpacity">: Ending Opacity</param>
		/// <param name="animatespeed">P: Speed Of Animation</param>
		/// <param name="pingpong">: PingPong Animation</param>
		/// <param name="numOfAnimations">: Number Of Recurring Animations Before Stopping ( 0 = Infinite )</param>
		FadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed = FADE_SPEED, bool pingpong = false, int numOfAnimations = 0);

		/// <summary>
		/// Fade Animation Setter
		/// </summary>
		/// <param name="startingOpacity">: Starting Opacity</param>
		/// <param name="endingOpacity">: Ending Opacity</param>
		/// <param name="animatespeed">P: Speed Of Animation</param>
		/// <param name="pingpong">: PingPong Animation</param>
		/// <param name="numOfAnimations">: Number Of Recurring Animations Before Stopping ( 0 = Infinite )</param>
		void initFadeAnimator(sf::Uint8 startingOpacity, sf::Uint8 endingOpacity, float animatespeed = FADE_SPEED, bool pingpong = false, int numOfAnimations = 0);

		//Fade Drawable
		template<typename T>
		void fadeDrawable(Drawables::D_Base<T>& obj) {

			//Opacity Increment
			float opacityIncr { std::abs(endOpacity - startOpacity) / (animationSpeed * exTime->getFrameRate()) };

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

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
	};
}

#endif // !ANIMATION_HPP
