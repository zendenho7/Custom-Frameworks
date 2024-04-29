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
	std::unique_ptr <Drawables::D_Sprite> spriteEntity;
	std::unique_ptr <Animation::SheetAnimator> sheetAnimator;
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
	//Button Init
	ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 50.0f), exEvents->windowCenter, 10.0f, 0.0f);
	ssEntity->initButtonText("CLICK THIS BUTTON", exAssets->fonts["COMIC"], sf::Color::Black, {0.75f, 0.4f});

	//Sprite Animation Init
	spriteEntity = std::make_unique<Drawables::D_Sprite>(exAssets->textures["AME"], sf::IntRect(0, 0, 500, 500), sf::Vector2f(150.0f, 150.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -100.0f));
	sheetAnimator = std::make_unique<Animation::SheetAnimator>(sf::Vector2u( 2000, 2500 ), sf::Vector2i(500, 500), Animation::ANIMATE_SPEED, true, sf::Vector2u(0, 0), sf::Vector2u(2, 4));

}

void SplashScreen::Update() {

	//Update Sprite Animation
	sheetAnimator->animateTexture(*spriteEntity);

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

	//Draw Sprite
	exEvents->window.draw(*spriteEntity);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
