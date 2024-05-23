/*****************************************************************************************************************
@file         MainMenu.hpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This is the header file of our main menu game state

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Utils.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

// ================================================================================
// Main Menu Namespace
// ================================================================================

namespace MainMenu {
    class State : public GSManager::GameState {
    private:

        //Game Objects
        std::unique_ptr<Drawables::D_Text> mmHeader;
        std::unique_ptr <Interface::RectButton> animationSS;
        std::unique_ptr <Interface::RectButton> golSS;
        std::unique_ptr <Interface::RectButton> exitBtn;

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
