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
#include "..\..\Header\Utility\Entity.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

namespace {
	std::unique_ptr <Interface::RectButton> ssEntity;
}

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("SFML", "../Assets/SFML Logo.png");
}

void SplashScreen::Init() {
	ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter);

	//ssEntity->setCustomHover(1.15f, 0.25f);
}

void SplashScreen::Update() {

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
	exEvents->window.draw(ssEntity->d_Rect);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
