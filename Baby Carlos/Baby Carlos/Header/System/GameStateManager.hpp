/*****************************************************************************************************************
@file         GameStateManager.hpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This is the header file to the gamestate manager

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef GS_MANAGER
#define GS_MANAGER

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\Menu\SplashScreen.hpp"
#include "..\..\Header\Menu\MainMenu.hpp"

// ================================================================================
// GS Manager Namespace
// ================================================================================

namespace GSManager {
	//GameState Constants
	enum GameStates : unsigned char {
		GS_SPLASH_SCREEN = 0,
		GS_MAIN_MENU,

		//DONT TOUCH GS
		GS_RESTART,
		GS_EXIT
	};

	//Function Pointer
	typedef void(*FP)(void);

	//GameState Functions
	void GameStateInit(GameStates startState);
	void GameStateUpdate(void);
}

#endif // !GS_MANAGER
