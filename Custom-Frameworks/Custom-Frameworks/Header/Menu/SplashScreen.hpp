/*****************************************************************************************************************
@file         SplashScreen.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file of our SplashScreen game state

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

// ================================================================================
// Splash Screen Namespace
// ================================================================================

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Animation.hpp"

namespace SplashScreen {
    class State : public GSManager::GameState {
    private:

        //Game Objects
        std::unique_ptr<Drawables::D_Sprite> ssSFML;
        std::unique_ptr<Animation::FadeAnimator> SFMLFadeAnimator;
        std::unique_ptr<Drawables::D_Text> ssText;

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

#endif // !SPLASHSCREEN_HPP
