/*****************************************************************************************************************
@file         MainMenu.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our main menu game state

Copyright (c) 2024 Zen Ho
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
	mmHeader = std::make_unique<Drawables::D_Text>("MAIN MENU", exAssets->fonts["COMIC"], sf::Color(0, 0, 0, 255), exEvents->windowCenter + sf::Vector2f(0.0f, -150.0f));
	mmHeader->Custom_OffsetToCenter();
	mmHeader->setScale(0.70f, 0.70f);
	mmHeader->Custom_SetFixedScale();

	//Animation Showcase Init
	animationSS = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, -50.0f), 15.0f, 0.0f);
	animationSS->initButtonText("ANIMATION SHOWCASE", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//GOL Showcase Init
	golSS = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 50.0f), 15.0f, 0.0f);
	golSS->initButtonText("GAMEOFLIFE SHOWCASE", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });

	//Exit Button Init
	exitBtn = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(250.0f, 75.0f), exEvents->windowCenter + sf::Vector2f(0.0f, 150.0f), 15.0f, 0.0f);
	exitBtn->initButtonText("EXIT APPLICATION", exAssets->fonts["COMIC"], sf::Color::Black, { 0.75f, 0.4f });
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
	animationSS->drawButton();

	//Draw Button To GOL Showcase
	golSS->drawButton();

	//Draw Exit Button
	exitBtn->drawButton();
}

void MainMenu::State::Free() {

}

void MainMenu::State::Unload() {

}
