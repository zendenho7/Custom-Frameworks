/*****************************************************************************************************************
@file         MainMenu.hpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This is the header file of our main menu game state

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "..\..\Header\System\GameStateManager.hpp"

// ================================================================================
// Main Menu Namespace
// ================================================================================

namespace MainMenu {
    class State : public GSManager::GameState {
    private:

        //Game Objects

    public:

        //GameState Components
        void Load() override;
        void Init() override;
        void Update() override;
        void Draw() override;
        void Free() override;
        void Unload() override;

        //Default Destructor
        ~State() override = default;
    };
}

#endif // !MAINMENU_HPP
