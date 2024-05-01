/*****************************************************************************************************************
@file         SplashScreen.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our SplashScreen game state

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Menu\SplashScreen.hpp"

#include "..\..\Header\Sandbox\AnimationShowcase.hpp"

void SplashScreen::State::Load() {
	//Load Textures
	exAssets->loadTexFromFile("SFML", "Assets/Textures/SFML Logo.png");
	exAssets->loadTexFromFile("AME", "Assets/Textures/ame.png");

	//Load Fonts
	exAssets->loadFontFromFile("COMIC", "Assets/Fonts/SuperComic.ttf");
	exAssets->loadFontFromFile("MONTSERRAT", "Assets/Fonts/Montserrat-Bold.ttf");
}

void SplashScreen::State::Init() {
	//SFML Logo SplashScreen Init
	ssSFML = std::make_unique<Drawables::D_Sprite>(exAssets->textures["SFML"], sf::IntRect(0, 0, 512, 512), sf::Vector2f(250.0f, 250.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -75.0f), 0.0f, sf::Uint8(0));
	SFMLFadeAnimator = std::make_unique<Animation::FadeAnimator>(sf::Uint8(0), sf::Uint8(255), 2.0f, true, 1);
	SFMLFadeAnimator2 = std::make_unique<Animation::FadeAnimator>(sf::Uint8(255), sf::Uint8(0), 1.0f, true, 1);

	//Splashscreen Text Init
	ssText = std::make_unique<Drawables::D_Text>("MADE USING SFML", exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, 125.0f));
	ssText->Custom_OffsetToCenter();
	ssText->setScale(0.4f, 0.4f);
	ssText->Custom_SetFixedScale();
}

void SplashScreen::State::Update() {

	SFMLFadeAnimator->fadeDrawable(*ssSFML);
	SFMLFadeAnimator->fadeDrawable(*ssText);

	if (SFMLFadeAnimator->isAnimationFinished()) {
		SFMLFadeAnimator2->fadeDrawable(*ssSFML);
		SFMLFadeAnimator2->fadeDrawable(*ssText);
	}

	//Button To Enter Next Game State
	if (SFMLFadeAnimator2->isAnimationFinished() || exEvents->mouseTriggered(sf::Mouse::Left)) {
		exGSManager->changeState(new AnimationSC::State());
	}

	//Restart GameState
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Escape)) {
		exGSManager->restartState();
	}
}

void SplashScreen::State::Draw() {

	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw Text
	exEvents->window.draw(*ssText);

	//Draw Sprite
	exEvents->window.draw(*ssSFML);
}

void SplashScreen::State::Free() {

}

void SplashScreen::State::Unload() {

}
