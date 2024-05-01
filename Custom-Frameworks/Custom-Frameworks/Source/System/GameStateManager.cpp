/*****************************************************************************************************************
@file         GameStateManager.cpp
@project      Custom Framworks
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
// Class: GameState Manager
// ================================================================================

GSManager::GameStateManager::GameStateManager(GameState* startingState)
	: b_GameRunning{ true }, b_ManipulatingState{ true }
{
	currGameState.reset(startingState);
	b_ManipulatingState = false;
	currGameState->Load();
	currGameState->Init();
}

void GSManager::GameStateManager::changeState(GameState* newState) {

	//Free & Unload Old State
	if (currGameState) {
		currGameState->Free();
		currGameState->Unload();
	}

	//Change New State
	prevGameState.swap(currGameState);
	currGameState.reset(newState);

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
}

bool GSManager::GameStateManager::getGameRunning() const {
	return b_GameRunning;
}
