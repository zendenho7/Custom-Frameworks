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
	std::unique_ptr<Entity::sprite> ssEntity;
}

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("TEST", "../Assets/playerFace.png");
}

void SplashScreen::Init() {
	ssEntity = std::make_unique<Entity::sprite>(Entity::sprite(exAssets->textures["TEST"], { 300.0f, 300.0f }, exSystemEvents->windowCenter, 0.0f, 255, true));
}

void SplashScreen::Update() {

	//Rotate Entity
	ssEntity->drawable.setRotation(ssEntity->drawable.getRotation() + 1);

	//Enter MainMenu Game State
	if (exSystemEvents->mouseTriggered(sf::Mouse::Button::Left)) {
		exGSNext = GSManager::GS_MAIN_MENU;
	}
}

void SplashScreen::Draw() {
	exSystemEvents->window.draw(ssEntity->bound);
	exSystemEvents->window.draw(ssEntity->drawable);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
