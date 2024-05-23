/*****************************************************************************************************************
@file         GameStateManager.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file manages all of the different gamestates in this application

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\GameStateManager.hpp"

//Include Paths To GameStates
#include "..\..\Header\Menu\SplashScreen.hpp"
#include "..\..\Header\Menu\MainMenu.hpp"
#include "..\..\Header\Sandbox\AnimationShowcase.hpp"
#include "..\..\Header\Sandbox\GridShowcase.hpp"

// ================================================================================
// Class: GameState Manager
// ================================================================================

//Private Member Function

GSManager::GameState * GSManager::GameStateManager::enumToGS(GSTypes gsType) {
	switch (gsType) {
	case GSTypes::GS_SPLASHSCREEN:
		return new SplashScreen::State();
		break;
	case GSTypes::GS_MAINMENU:
		return new MainMenu::State();
		break;
	case GSTypes::GS_ANIMATION_SC:
		return new AnimationSC::State();
		break;
	case GSTypes::GS_GRID_SC:
		return new GridSC::State();
		break;
	default:
		return 0;
		break;
	}
}

//Public Member Function

GSManager::GameStateManager::GameStateManager(GSTypes startingGS)
	: b_GameRunning{ true }, b_ManipulatingState{ true }
{
	currGameState.reset(enumToGS(startingGS));
	b_ManipulatingState = false;
	currGameState->Load();
	currGameState->Init();
}

void GSManager::GameStateManager::changeState(GSTypes newGS) {

	//Free & Unload Old State
	if (currGameState) {
		currGameState->Free();
		currGameState->Unload();
	}

	//Change New State
	prevGameState.swap(currGameState);
	currGameState.reset(enumToGS(newGS));

	//Load & Init New State
	if (currGameState) {
		currGameState->Load();
		currGameState->Init();
	}
}

void GSManager::GameStateManager::updateGameState() {
	if(currGameState)
	currGameState->Update();
}

void GSManager::GameStateManager::drawGameState() {
	if (currGameState)
		currGameState->Draw();
}

void GSManager::GameStateManager::restartState() {
	if (currGameState) {
		currGameState->Free();
		currGameState->Init();
	}
}

void GSManager::GameStateManager::previousState() {
	//Free & Unload Old State
	if (currGameState) {
		currGameState->Free();
		currGameState->Unload();
	}

	//Change New State
	prevGameState.swap(currGameState);

	//Load & Init New State
	if (currGameState) {
		currGameState->Load();
		currGameState->Init();
	}
}

void GSManager::GameStateManager::exitGame() {
	b_GameRunning = false;

	currGameState->Free();
	currGameState->Unload();

	prevGameState->Free();
	prevGameState->Unload();
}

bool GSManager::GameStateManager::getGameRunning() const {
	return b_GameRunning;
}
