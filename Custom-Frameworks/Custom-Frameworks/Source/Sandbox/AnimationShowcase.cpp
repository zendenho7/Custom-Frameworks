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
#include "..\..\Header\Utility\Utils.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Animation.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

namespace {
	std::unique_ptr <Interface::RectButton> stopButton;
	std::unique_ptr <Interface::RectButton> resumeButton;
	std::unique_ptr <Interface::RectButton> restartButton;
	std::unique_ptr <Drawables::D_Sprite> spriteEntity;
	std::unique_ptr <Animation::SheetAnimator> sheetAnimator;
	std::unique_ptr<Drawables::D_Text> animationStatus;
}

void AnimationSC::Load() {
	//Load Textures
	exAssets->loadTexFromFile("SFML", "Assets/Textures/SFML Logo.png");
	exAssets->loadTexFromFile("AME", "Assets/Textures/ame.png");

	//Load Fonts
	exAssets->loadFontFromFile("COMIC", "Assets/Fonts/SuperComic.ttf");
	exAssets->loadFontFromFile("MONTSERRAT", "Assets/Fonts/Montserrat-Bold.ttf");
}

void AnimationSC::Init() {

	//Animation Status Init
	animationStatus = std::make_unique<Drawables::D_Text>("ANIMATION ONGOING", exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, -250.0f));
	animationStatus->Custom_OffsetToCenter();
	animationStatus->setScale(0.4f, 0.4f);
	animationStatus->Custom_SetFixedScale();

	//Sprite Animation Init
	spriteEntity = std::make_unique<Drawables::D_Sprite>(exAssets->textures["AME"], sf::IntRect(0, 0, 500, 500), sf::Vector2f(250.0f, 250.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -75.0f));
	sheetAnimator = std::make_unique<Animation::SheetAnimator>(sf::Vector2u(2000, 2500), sf::Vector2i(500, 500), sf::Vector2u(0, 0), sf::Vector2u(2, 4), 1.0f, true, 5);

	//Stop Button Init
	stopButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 100.0f), 15.0f, 0.0f);
	stopButton->initButtonText("STOP ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Start Button Init
	resumeButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 175.0f), 15.0f, 0.0f);
	resumeButton->initButtonText("RESUME ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Restart Button Init
	restartButton = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 250.0f), 15.0f, 0.0f);
	restartButton->initButtonText("RESTART ANIMATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });
}

void AnimationSC::Update() {

	//Update Sprite Animation
	sheetAnimator->animateTexture(*spriteEntity);

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

	//Restart Animation
	if (restartButton->isButtonClicked()) {
		sheetAnimator->restartAnimation();
		animationStatus->setString("ANIMATION ONGOING");
	}

	//Animation Finished
	if (sheetAnimator->isAnimationFinished()) {
		animationStatus->setString("ANIMATION FINISHED");
	}
}

void AnimationSC::Draw() {

	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw Text
	exEvents->window.draw(*animationStatus);

	//Draw Sprite
	exEvents->window.draw(*spriteEntity);

	//Draw Buttons
	stopButton->drawButton();
	resumeButton->drawButton();
	restartButton->drawButton();
}

void AnimationSC::Free() {

}

void AnimationSC::Unload() {

}