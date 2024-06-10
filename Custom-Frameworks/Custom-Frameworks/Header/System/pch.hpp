/*****************************************************************************************************************
@file         pch.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This file includes all the external include header file

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef PCH_HPP
#define PCH_HPP

// ================================================================================
// #DEFINES
// ================================================================================

#define _USE_MATH_DEFINES

// ================================================================================
// SFML INCLUDES
// ================================================================================
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// ================================================================================
// STL INCLUDES
// ================================================================================

#include <crtdbg.h> // To check for memory leaks
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <Windows.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <cassert>
#include <chrono>
#include <limits>

#endif // !PCH_HPP
