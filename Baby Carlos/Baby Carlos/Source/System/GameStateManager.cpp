/*****************************************************************************************************************
@file         GameStateManager.cpp
@project      SUPER CARLOS
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

GSManager::GameStates exGSCurrent = GSManager::GS_SPLASH_SCREEN, exGSNext = GSManager::GS_SPLASH_SCREEN, exGSPrevious = GSManager::GS_SPLASH_SCREEN;
GSManager::FP exFPLoad = nullptr, exFPInit = nullptr, exFPUpdate = nullptr, exFPDraw = nullptr, exFPFree = nullptr, exFPUnload = nullptr;

// ================================================================================
// Functions: GameState Management Functions
// ================================================================================
void GSManager::GameStateInit(GameStates startState) {
	exGSPrevious = exGSCurrent = exGSNext = startState;
}

void GSManager::GameStateUpdate() {

	switch (exGSCurrent) {
	case GS_SPLASH_SCREEN:
		exFPLoad = SplashScreen::Load;
		exFPInit = SplashScreen::Init;
		exFPUpdate = SplashScreen::Update;
		exFPDraw = SplashScreen::Draw;
		exFPFree = SplashScreen::Free;
		exFPUnload = SplashScreen::Unload;
		break;
	case GS_MAIN_MENU:
		exFPLoad = MainMenu::Load;
		exFPInit = MainMenu::Init;
		exFPUpdate = MainMenu::Update;
		exFPDraw = MainMenu::Draw;
		exFPFree = MainMenu::Free;
		exFPUnload = MainMenu::Unload;
		break;
	default:
		break;
	}
}
