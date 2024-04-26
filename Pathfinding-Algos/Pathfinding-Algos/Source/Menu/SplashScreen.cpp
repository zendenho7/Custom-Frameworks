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
	std::unique_ptr <Entity::sprite> spriteEntity;
}

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("SFML", "../Assets/SFML Logo.png");
	exAssets->addTexFromFile("AME", "../Assets/ame.png");
}

void SplashScreen::Init() {
	ssEntity = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter);
	spriteEntity = std::make_unique<Entity::sprite>(exAssets->textures["AME"], sf::Vector2i(4, 5), sf::Vector2f(200.0f, 200.0f), exEvents->windowCenter);

	spriteEntity->animate.SetSpriteSheet(sf::Vector2i(2000, 2500), sf::Vector2i(500, 500), 0.5f, true, sf::Vector2i(0, 0), sf::Vector2i(1000, 2000));
}

void SplashScreen::Update() {

	spriteEntity->animate.animateTexture(spriteEntity->d_Sprite);

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
	exEvents->window.draw(spriteEntity->d_Sprite);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
