/*****************************************************************************************************************
@file         SplashScreen.cpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This file contains our SplashScreen game state

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Menu\SplashScreen.hpp"
#include "..\..\Header\System\Utils.hpp"

namespace SplashScreen {
	std::unique_ptr<Entity::rect> ssEntity;
}

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("TEST", "../Assets/playerFace.png");
}

void SplashScreen::Init() {
	ssEntity = std::make_unique<Entity::rect>(Entity::rect({255, 255, 255, 255}, {300.0f, 300.0f}, exEvents->windowCenter, 255));
}

void SplashScreen::Update() {

	//Rotate Entity
	ssEntity->drawableRect.setRotation(ssEntity->drawableRect.getRotation() + 1);
	//ssEntity->bound.setRotation(ssEntity->drawable.getRotation());

	//Enter MainMenu Game State
	if (exEvents->mouseTriggered(sf::Mouse::Button::Left)) {
		exGSNext = GSManager::GS_MAIN_MENU;
	}
}

void SplashScreen::Draw() {

	//Clear Window
	exEvents->window.clear();

	//Draw To Window
	exEvents->window.draw(ssEntity->drawableRect);
	//exEvents->window.draw(ssEntity->drawable);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
