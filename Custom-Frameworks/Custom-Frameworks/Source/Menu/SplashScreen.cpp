/*****************************************************************************************************************
@file         SplashScreen.cpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This file contains our SplashScreen game state

Copyright � 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Menu\SplashScreen.hpp"

void SplashScreen::State::Load() {
	//Load Textures
	exAssets->loadTexFromFile("SFML", "Assets/Textures/SFML Logo.png");
	exAssets->loadTexFromFile("AME", "Assets/Textures/ame.png");

	//Load Fonts
	exAssets->loadFontFromFile("COMIC", "Assets/Fonts/SuperComic.ttf");
	exAssets->loadFontFromFile("MONTSERRAT", "Assets/Fonts/Montserrat-Bold.ttf");

	//Set Primary Font
	exAssets->setPrimaryFont("MONTSERRAT");

	//Set Secondary Font
	exAssets->setSecondaryFont("COMIC");
}

void SplashScreen::State::Init() {
	//SFML Logo SplashScreen Init
	ssSFML = std::make_unique<Drawables::D_Sprite>(exAssets->getTexture("SFML"), sf::IntRect(0, 0, 512, 512), sf::Vector2f(250.0f, 250.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -75.0f), 0.0f, sf::Uint8(0));
	SFMLFadeAnimator = std::make_unique<Animation::FadeAnimator>(sf::Uint8(0), sf::Uint8(255), 5.0f, true, 2);

	//Splashscreen Text Init
	ssText = std::make_unique<Drawables::D_Text>("MADE USING SFML", exAssets->getPrimaryFont(), sf::Color(0, 0, 0, 0), exEvents->windowCenter + sf::Vector2f(0.0f, 125.0f));
	ssText->Custom_OffsetToCenter();
	ssText->setScale(0.4f, 0.4f);
	ssText->Custom_SetFixedScale();

	//Set Frame Time Display
	exTime->setDisplay(exAssets->getPrimaryFont(), sf::Color::Black, Drawables::Origin::TOP_LEFT);
}

void SplashScreen::State::Update() {

	//Drawables To Fade
	SFMLFadeAnimator->fadeDrawable(*ssSFML);
	SFMLFadeAnimator->fadeDrawable(*ssText);

	//Speed Up Animation
	if (SFMLFadeAnimator->getCompletedAnimations() == 1) {
		SFMLFadeAnimator->initSheetAnimatorSpeed(1.0f);
	}

	//Button To Enter Next Game State
	if (SFMLFadeAnimator->isAnimationFinished() || exEvents->mouseTriggered(sf::Mouse::Left)) {
		exGSManager->changeState(GSManager::GSTypes::GS_MAINMENU);
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
