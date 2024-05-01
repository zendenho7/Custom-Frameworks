/*****************************************************************************************************************
@file         GameStateManager.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file to the gamestate manager

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef GS_MANAGER
#define GS_MANAGER

// ================================================================================
// GS Manager Namespace
// ================================================================================

namespace GSManager {

	//Application GameStates
	enum class GSTypes {
		GS_SPLASHSCREEN = 0,
		GS_MAINMENU,
		GS_ANIMATION_SC
	};

	//GameState Class
	class GameState {
	public:
		virtual void Load() = 0;
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Free() = 0;
		virtual void Unload() = 0;

		virtual ~GameState() = default;
	};

	class GameStateManager {
	private:
		//Curr & Prev GameState
		std::unique_ptr<GameState> currGameState;
		std::unique_ptr<GameState> prevGameState;

		//Flag For Game Running
		bool b_GameRunning;

		//Flag To Signify Changes To currGameState
		bool b_ManipulatingState;

		//Conversion From Enum To GameSatet Ptr
		GameState* enumToGS(GSTypes gsType);

	public:
		//Default Constructor
		GameStateManager(GSTypes startingGS);

		//Change Game State
		void changeState(GSTypes newGS);

		//Update GameState
		void updateGameState();

		//Draw GameState
		void drawGameState();

		//Restart GameState
		void restartState();

		//Go To Previous GameState
		void previousState();
		
		//Exit Game
		void exitGame();

		//Get GameRunning Status Flag
		bool getGameRunning() const;
	};
}

#endif // !GS_MANAGER
