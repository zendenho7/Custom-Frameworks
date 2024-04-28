/*****************************************************************************************************************
@file         Utils.hpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the header file for this application's utility functions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\System\Load.hpp"

// ================================================================================
// EXTERNALS
// ================================================================================

extern Systems::EventHandler* exEvents;
extern Systems::FrameTime* exTime;
extern Load::Assets* exAssets;

// ================================================================================
// MATHEMATICAL HELPERS
// ================================================================================

/// <summary>
/// Pythagoreom Function To Find a, b or c
/// </summary>
/// <param name="a">: a, b or c</param>
/// <param name="b">: a, b or c</param>
/// <param name="hyp">: looking for hyp if true, else looking for edge</param>
/// <returns></returns>
float PythagoreomFunction(float a, float b, bool hyp);

#endif // !UTILS_HPP
