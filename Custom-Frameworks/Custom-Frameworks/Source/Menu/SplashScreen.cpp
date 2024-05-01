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
#include "..\..\Header\Utility\Utils.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Animation.hpp"

namespace {
	std::unique_ptr<Drawables::D_Sprite> ssSFML;
	std::unique_ptr<Animation::FadeAnimator> SFMLFadeAnimator;
	std::unique_ptr<Animation::FadeAnimator> SFMLFadeAnimator2;
	std::unique_ptr<Drawables::D_Text> ssText;
}

void SplashScreen::Load() {
	//Load Textures
	exAssets->loadTexFromFile("SFML", "Assets/Textures/SFML Logo.png");
	exAssets->loadTexFromFile("AME", "Assets/Textures/ame.png");

	//Load Fonts
	exAssets->loadFontFromFile("COMIC", "Assets/Fonts/SuperComic.ttf");
	exAssets->loadFontFromFile("MONTSERRAT", "Assets/Fonts/Montserrat-Bold.ttf");
}

void SplashScreen::Init() {
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

void SplashScreen::Update() {

	SFMLFadeAnimator->fadeDrawable(*ssSFML);
	SFMLFadeAnimator->fadeDrawable(*ssText);

	if (SFMLFadeAnimator->isAnimationFinished()) {
		SFMLFadeAnimator2->fadeDrawable(*ssSFML);
		SFMLFadeAnimator2->fadeDrawable(*ssText);
	}

	//Button To Enter Next Game State
	if (SFMLFadeAnimator2->isAnimationFinished() || exEvents->mouseTriggered(sf::Mouse::Left)) {
		exGSNext = GSManager::GS_ANIMATION_SC;
	}
}

void SplashScreen::Draw() {

	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw Text
	exEvents->window.draw(*ssText);

	//Draw Sprite
	exEvents->window.draw(*ssSFML);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
