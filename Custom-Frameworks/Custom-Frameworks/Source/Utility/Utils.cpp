/*****************************************************************************************************************
@file         Utils.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains the definitions of utility functions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Utils.hpp"

// ================================================================================
// MATHEMATICAL HELPERS
// ================================================================================

float PythagoreomFunction(float a, float b, bool hyp) {
	if (hyp) {
		return static_cast<float>(std::sqrt(std::powf(a, 2) + std::powf(b, 2)));
	}
	else {
		return static_cast<float>(std::sqrt(std::powf(a > b ? a : b, 2) - std::powf(a > b ? b : a, 2)));
	}
}
