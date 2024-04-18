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

void SplashScreen::Load() {
	//Load All Essential Assets For The Game Here
	exAssets->addTexFromFile("TEST", "../Assets/playerFace.png");
}

void SplashScreen::Init() {

}

void SplashScreen::Update() {
}

void SplashScreen::Draw() {
	sf::Sprite testSprite;

	testSprite.setTexture(exAssets->textures["TEST"]);
	exSystemEvents->window.draw(testSprite);
}

void SplashScreen::Free() {

}

void SplashScreen::Unload() {

}
