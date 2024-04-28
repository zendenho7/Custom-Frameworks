/*****************************************************************************************************************
@file         SplashScreen.cpp
@project      Pathfinding Algorithms
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
#include "..\..\Header\Utility\UserInterface.hpp"

namespace {
	std::unique_ptr <Interface::RectButton> ssEntity;
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
	ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(377.0f, 62.0f), exEvents->windowCenter, 5.0f);
	ssEntity->initButtonText("BUTTON", exAssets->fonts["COMIC"], sf::Color::Black, 72);
	ssEntity->setOutlineThickness(10.0f);
	ssEntity->setOutlineColor(sf::Color::Red);
}

void SplashScreen::Update() {

	//spriteAnimator->animateTexture(*spriteEntity);

	//Rotate Entity
	if (ssEntity->isButtonClicked()) {
		exGSNext = GSManager::GS_MAIN_MENU;
	}

	//Enter MainMenu Game State
	//if (exEvents->mouseTriggered(sf::Mouse::Button::Left)) {
	//	exGSNext = GSManager::GS_MAIN_MENU;
	//}
}

void SplashScreen::Draw() {

	//Clear Window
	exEvents->window.clear();

	//Draw To Window
	exEvents->window.draw(*ssEntity);
	exEvents->window.draw(ssEntity->getButtonText());
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
