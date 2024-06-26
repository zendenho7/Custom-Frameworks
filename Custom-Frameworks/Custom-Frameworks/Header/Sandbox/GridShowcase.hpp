/*****************************************************************************************************************
@file         AnimationShowcase.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file of our Grid Showcase

Copyright � 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef GRIDSHOWCASE_HPP
#define GRIDSHOWCASE_HPP

// ================================================================================
// Splash Screen Namespace
// ================================================================================

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"
#include "..\..\Header\GameObjects\Map.hpp"

namespace GridSC {
    class State : public GSManager::GameState {
    private:
        //Game Objects
        std::unique_ptr<Map::Grid> GOLGrid;
        std::unique_ptr<Drawables::D_Text> GOLHeader;
        std::unique_ptr<Drawables::D_Text> GOLStatus;

        //Left & Right Toggle Save Data
        std::unique_ptr <Interface::RectButton> nextData;
        std::unique_ptr <Interface::RectButton> prevData;
        int dataIndexTracker;

        //Saved Grids
        std::vector<std::string> savedGridData;
        
        //Buffer Boolean Array
        std::vector<std::vector<bool>> selectedArray;
        
        //Simulation Paused
        bool b_SimPaused;

        //BG Color Of GOL Sim
        sf::Color bgColor;

        //Helper Buttons DropDown
        std::unique_ptr<Interface::DropDown> helperDropDown;

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

        //Helper Functions
        void GOLUpdateLogic();
    };
}

#endif // !GRIDSHOWCASE_HPP