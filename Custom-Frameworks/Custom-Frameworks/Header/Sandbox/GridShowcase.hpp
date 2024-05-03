/*****************************************************************************************************************
@file         AnimationShowcase.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file of our Grid Showcase

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef GRIDSHOWCASE_HPP
#define GRIDSHOWCASE_HPP

// ================================================================================
// Splash Screen Namespace
// ================================================================================

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Animation.hpp"
#include "..\..\Header\GameObjects\Map.hpp"

namespace GridSC {
    class State : public GSManager::GameState {
    private:
        //Game Objects
        std::unique_ptr<Map::Grid> testGrid;

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

#endif // !GRIDSHOWCASE_HPP