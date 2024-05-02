/*****************************************************************************************************************
@file         GridShowcase.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our Grid Showcase Definitions

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Sandbox\GridShowcase.hpp"


void GridSC::State::Load() {

}

void GridSC::State::Init() {
	testGrid = std::make_unique<Map::Grid>(sf::Vector2<size_t>(50, 25), exEvents->windowCenter, sf::Vector2f(10.0f, 10.0f), sf::Color::Black, sf::Color::White, sf::Vector2f(25.0f, 25.0f), 10.0f);
}

void GridSC::State::Update() {

	//Go Back To Previous State
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Escape)) {
		exGSManager->exitGame();
	}
}

void GridSC::State::Draw() {

	//Clear Window
	exEvents->window.clear({ 100, 100, 100, 255 });

	testGrid->drawGrid();
}

void GridSC::State::Free() {

}

void GridSC::State::Unload() {

}