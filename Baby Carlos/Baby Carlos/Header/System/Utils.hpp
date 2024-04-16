/*****************************************************************************************************************
@file         Utils.hpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This is the header files for this application's utility functions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\System\Systems.hpp"

#ifndef UTILS_HPP
#define UTILS_HPP

// ================================================================================
// EXTERALS
// ================================================================================

//GameStates
extern GSManager::GameStates current, next, previous;
extern GSManager::FP fpLoad, fpInit, fpUpdate, fpDraw, fpFree, fpUnload;

//Window & Events
extern Systems::EventHandler* systemEvents;

#endif // !UTILS_HPP
