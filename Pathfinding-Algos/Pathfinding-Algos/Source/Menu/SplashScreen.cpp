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
	//std::unique_ptr <Interface::RectButton> ssEntity;
	//std::unique_ptr <sf::Sprite> spriteEntity;
	//std::unique_ptr <Animation::SheetAnimator> spriteAnimator;
	std::unique_ptr <Drawables::RoundedRect> roundedRect;
}

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("SFML", "Assets/SFML Logo.png");
	exAssets->addTexFromFile("AME", "Assets/ame.png");
}

void SplashScreen::Init() {
	//ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, "test", sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter);
	//spriteEntity = std::make_unique<sf::Sprite>();
	//Drawables::initSprite(*spriteEntity, exAssets->textures["AME"], sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(500, 500)), sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter);
	//spriteAnimator = std::make_unique<Animation::SheetAnimator>(spriteEntity->getTexture()->getSize(), spriteEntity->getTextureRect().getSize(), 0.15f, true, sf::Vector2u(0, 0), sf::Vector2u(2, 4));
	roundedRect = std::make_unique<Drawables::RoundedRect>(sf::Color::White, sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter, 100.0f);
}

void SplashScreen::Update() {

	//spriteAnimator->animateTexture(*spriteEntity);

	//Rotate Entity
	//if (ssEntity->isButtonClicked()) {
	//	exGSNext = GSManager::GS_MAIN_MENU;
	//}

	//Enter MainMenu Game State
	//if (exEvents->mouseTriggered(sf::Mouse::Button::Left)) {
	//	exGSNext = GSManager::GS_MAIN_MENU;
	//}
}

void SplashScreen::Draw() {

	//Clear Window
	//exEvents->window.clear();

	//Draw To Window
	exEvents->window.draw(*roundedRect);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
