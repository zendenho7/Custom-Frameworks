/*****************************************************************************************************************
@file         Utils.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file for this application's utility functions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
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
extern Systems::TimeHandler* exTime;
extern Systems::DataHandler* exData;
extern Load::Assets* exAssets;
extern GSManager::GameStateManager* exGSManager;

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
