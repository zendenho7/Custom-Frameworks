/*****************************************************************************************************************
@file         MainMenu.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our main menu game state

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Menu\MainMenu.hpp"

void MainMenu::State::Load() {

}

void MainMenu::State::Init() {
	//Main Menu Header Init
	mmHeader = std::make_unique<Drawables::D_Text>("MAIN MENU", exAssets->getPrimaryFont(), sf::Color(0, 0, 0, 255), exEvents->windowCenter + sf::Vector2f(0.0f, -150.0f));
	mmHeader->Custom_OffsetToCenter();
	mmHeader->setScale(0.70f, 0.70f);
	mmHeader->Custom_SetFixedScale();

	//Animation Showcase Init
	animationSS = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -50.0f), 15.0f, 0.0f);
	animationSS->initRectButtonText("ANIMATION SHOWCASE", exAssets->getPrimaryFont(), sf::Color::Black);

	//GOL Showcase Init
	golSS = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 50.0f), 15.0f, 0.0f);
	golSS->initRectButtonText("GAMEOFLIFE SHOWCASE", exAssets->getPrimaryFont(), sf::Color::Black);

	//Exit Button Init
	exitBtn = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 150.0f), 15.0f, 0.0f);
	exitBtn->initRectButtonText("EXIT APPLICATION", exAssets->getPrimaryFont(), sf::Color::Black);
}

void MainMenu::State::Update() {
	//Animation Button
	if (animationSS->isButtonClicked()) {
		exGSManager->changeState(GSManager::GSTypes::GS_ANIMATION_SC);
	}

	//GOL Button
	if (golSS->isButtonClicked()) {
		exGSManager->changeState(GSManager::GSTypes::GS_GRID_SC);
	}

	//GOL Button
	if (exitBtn->isButtonClicked()) {
		exGSManager->exitGame();
	}
}

void MainMenu::State::Draw() {
	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw Text
	exEvents->window.draw(*mmHeader);

	//Draw Button To Animation Showcase
	animationSS->Custom_Draw();

	//Draw Button To GOL Showcase
	golSS->Custom_Draw();

	//Draw Exit Button
	exitBtn->Custom_Draw();
}

void MainMenu::State::Free() {

}

void MainMenu::State::Unload() {

}
