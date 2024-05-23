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
	mainmenuPanel = std::make_unique<Interface::Panel>(sf::Color::Cyan, sf::Vector2f(500.0f, 500.0f), exEvents->windowCenter, 10.0f);
	mainmenuPanel->addSpriteComponent("TESTSPRITE", 0.3f, exAssets->getTexture("SFML"), sf::IntRect(0, 0, 512, 512), 255);
	mainmenuPanel->addTextComponent("HEADER", 0.1f, "MAIN MENU", exAssets->getPrimaryFont(), sf::Color(0, 0, 0, 255));
	mainmenuPanel->addButtonComponent("ANIMATION", 0.2f, sf::Color::White, 10.0f, "ANIMATION SHOWCASE", exAssets->getPrimaryFont(), sf::Color::Black);
	mainmenuPanel->addButtonComponent("GAME OF LIFE", 0.2f, sf::Color::White, 10.0f, "GAMEOFLIFE SHOWCASE", exAssets->getPrimaryFont(), sf::Color::Black);
	mainmenuPanel->addButtonComponent("EXIT", 0.2f, sf::Color::White, 10.0f, "EXIT APPLICATION", exAssets->getPrimaryFont(), sf::Color::Black);
	mainmenuPanel->arrangeComponents(sf::Vector2f(75.0f, 50.0f), 25.0f, Interface::PanelArrangment::VERTICAL);
}

void MainMenu::State::Update() {
	//Animation Button
	if (mainmenuPanel->isButtonClicked("ANIMATION")) {
		exGSManager->changeState(GSManager::GSTypes::GS_ANIMATION_SC);
	}

	////GOL Button
	if (mainmenuPanel->isButtonClicked("GAME OF LIFE")) {
		exGSManager->changeState(GSManager::GSTypes::GS_GRID_SC);
	}

	////GOL Button
	if (mainmenuPanel->isButtonClicked("EXIT")) {
		exGSManager->exitGame();
	}
}

void MainMenu::State::Draw() {
	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	//Draw MainMenu Panel
	mainmenuPanel->drawPanel();
}

void MainMenu::State::Free() {

}

void MainMenu::State::Unload() {

}
