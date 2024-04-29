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
	ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter, 10.0f, 0.0f);
	ssEntity->initButtonText("CLICK THIS BUTTON", exAssets->fonts["COMIC"], sf::Color::Black, {0.75f, 0.4f});
}

void SplashScreen::Update() {

	//Button To Enter Next Game State
	if (ssEntity->isButtonClicked()) {
		exGSNext = GSManager::GS_MAIN_MENU;
	}
}

void SplashScreen::Draw() {

	//Clear Window
	exEvents->window.clear({100, 100, 100, 255});

	//Draw To Window
	ssEntity->drawButton();
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
