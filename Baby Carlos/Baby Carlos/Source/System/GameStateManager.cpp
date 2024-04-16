/*****************************************************************************************************************
@file         GameStateManager.cpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This file manages all of the different gamestates in this application

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\GameStateManager.hpp"

// ================================================================================
// EXTERNALS
// ================================================================================

GSManager::GameStates current = GSManager::GS_SPLASH_SCREEN, next = GSManager::GS_SPLASH_SCREEN, previous = GSManager::GS_SPLASH_SCREEN;
GSManager::FP fpLoad = nullptr, fpInit = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

// ================================================================================
// Functions: GameState Management Functions
// ================================================================================
void GSManager::GameStateInit(GameStates startState) {
	previous = current = next = startState;
}

void GSManager::GameStateUpdate() {

	switch (current) {
	case GS_SPLASH_SCREEN:
		fpLoad = SplashScreen::Load;
		fpInit = SplashScreen::Init;
		fpUpdate = SplashScreen::Update;
		fpDraw = SplashScreen::Draw;
		fpFree = SplashScreen::Free;
		fpUnload = SplashScreen::Unload;
		break;
	case GS_MAIN_MENU:
		fpLoad = MainMenu::Load;
		fpInit = MainMenu::Init;
		fpUpdate = MainMenu::Update;
		fpDraw = MainMenu::Draw;
		fpFree = MainMenu::Free;
		fpUnload = MainMenu::Unload;
		break;
	default:
		break;
	}
}
