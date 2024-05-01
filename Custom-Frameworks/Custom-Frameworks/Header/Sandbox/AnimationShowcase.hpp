/*****************************************************************************************************************
@file         AnimationShowcase.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file of our Animation Showcase

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef ANIMATIONSHOWCASE_HPP
#define ANIMATIONSHOWCASE_HPP

// ================================================================================
// Splash Screen Namespace
// ================================================================================

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Animation.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

namespace AnimationSC {
    class State : public GSManager::GameState {
    private:

        //Game Objects
        std::unique_ptr <Interface::RectButton> stopButton;
        std::unique_ptr <Interface::RectButton> resumeButton;
        std::unique_ptr <Interface::RectButton> restartButton;
        std::unique_ptr <Interface::RectButton> endButton;
        std::unique_ptr <Drawables::D_Sprite> spriteEntity;
        std::unique_ptr <Animation::SheetAnimator> sheetAnimator;
        std::unique_ptr<Drawables::D_Text> animationStatus;
        std::unique_ptr<Drawables::D_Text> animationCount;
        std::unique_ptr <Interface::RectButton> increaseButton;
        std::unique_ptr <Interface::RectButton> decreaseButton;

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

#endif // !ANIMATIONSHOWCASE_HPP