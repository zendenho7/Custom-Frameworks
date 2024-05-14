/*****************************************************************************************************************
@file         AnimationShowcase.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our Animation Showcase Definitions

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Sandbox\AnimationShowcase.hpp"


void AnimationSC::State::Load() {

}

void AnimationSC::State::Init() {

	//Sprite Animation Init
	spriteEntity = std::make_unique<Drawables::D_Sprite>(exAssets->textures["AME"], sf::IntRect(0, 0, 500, 500), sf::Vector2f(250.0f, 250.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -75.0f));
	sheetAnimator = std::make_unique<Animation::SheetAnimator>(sf::Vector2u(2000, 2500), sf::Vector2i(500, 500), sf::Vector2u(0, 0), sf::Vector2u(2, 4), 1.0f, false , 5);

	//Stop Button Init
	stopButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 100.0f), 15.0f, 0.0f);
	stopButton->initButtonText("PAUSE ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Start Button Init
	resumeButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 175.0f), 15.0f, 0.0f);
	resumeButton->initButtonText("RESUME ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Restart Button Init
	restartButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 250.0f), 15.0f, 0.0f);
	restartButton->initButtonText("RESTART ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//End Button Init
	endButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 325.0f), 15.0f, 0.0f);
	endButton->initButtonText("END ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Animation Status Init
	animationCount = std::make_unique<Drawables::D_Text>(std::move((std::to_string(sheetAnimator->getCompletedAnimations()) += " / ") += sheetAnimator->getAnimationsToComplete() ? std::move(std::to_string(sheetAnimator->getAnimationsToComplete())) : "INF"), exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, -300.0f));
	animationCount->Custom_OffsetToCenter();
	animationCount->setScale(0.4f, 0.4f);
	animationCount->Custom_SetFixedScale();

	//Animation Status Init
	animationStatus = std::make_unique<Drawables::D_Text>("ANIMATION ONGOING", exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, -250.0f));
	animationStatus->Custom_OffsetToCenter();
	animationStatus->setScale(0.4f, 0.4f);
	animationStatus->Custom_SetFixedScale();

	//Increase Button
	increaseButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(100.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(75.0f, 325.0f), 15.0f, 0.0f);
	increaseButton->initButtonText("ADD", exAssets->fonts["COMIC"], sf::Color::Black, { 0.5f, 0.5f });

	//Decrease Button
	decreaseButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(100.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(-75.0f, 325.0f), 15.0f, 0.0f);
	decreaseButton->initButtonText("SUB", exAssets->fonts["COMIC"], sf::Color::Black, { 0.5f, 0.5f });
}

void AnimationSC::State::Update() {

	//Update Sprite Animation
	sheetAnimator->animateTexture(*spriteEntity);

	//Restart Animation
	if (restartButton->isButtonClicked()) {
		sheetAnimator->restartAnimation();
		animationStatus->setString("ANIMATION ONGOING");
	}

	if (sheetAnimator->isAnimationFinished()) {
		//Increase Animation Count
		if (increaseButton->isButtonClicked()) {
			sheetAnimator->setAnimationsToComplete(sf::Uint8(sheetAnimator->getAnimationsToComplete() + 1));
		}

		//Decrease Animation Count
		if (decreaseButton->isButtonClicked()) {
			sheetAnimator->setAnimationsToComplete(sf::Uint8(sheetAnimator->getAnimationsToComplete() - 1));
		}

		//Set Animation Status
		animationStatus->setString("ANIMATION FINISHED");
	}
	else {

		//Stop Animation
		if (stopButton->isButtonClicked()) {
			sheetAnimator->stopAnimation();
			animationStatus->setString("ANIMATION PAUSED");
		}

		//Resume Animation
		if (resumeButton->isButtonClicked()) {
			sheetAnimator->resumeAnimation();
			animationStatus->setString("ANIMATION ONGOING");
		}

		//End Animation
		if (endButton->isButtonClicked()) {
			sheetAnimator->setAnimationFinished();
		}
	}

	//Update Animation Count
	animationCount->setString(std::move(std::to_string(sheetAnimator->getCompletedAnimations()) += " / ") += std::move(sheetAnimator->getAnimationsToComplete() ? std::to_string(sheetAnimator->getAnimationsToComplete()) : "INF"));

	//Go Back To Main Menu Game State
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Escape)) {
		exGSManager->previousState();
	}
}

void AnimationSC::State::Draw() {

	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw Text
	exEvents->window.draw(*animationCount);
	exEvents->window.draw(*animationStatus);

	//Draw Sprite
	exEvents->window.draw(*spriteEntity);

	//Draw Buttons
	restartButton->drawButton();

	if (sheetAnimator->isAnimationFinished()) {
		increaseButton->drawButton();
		decreaseButton->drawButton();
	}
	else {
		stopButton->drawButton();
		resumeButton->drawButton();
		endButton->drawButton();
	}
}

void AnimationSC::State::Free() {

}

void AnimationSC::State::Unload() {

}