/*****************************************************************************************************************
@file         Load.cpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This file contains all the defintions of loading functionalities in the project

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Load.hpp"

// ================================================================================
// Function: Load Assets Constructor
// ================================================================================

// ================================================================================
// Function: Add Texture Member Function
// ================================================================================

void Load::Assets::addTexFromFile(std::string const& texIdentifier, std::string const& texturePath) {
	textures.emplace(texIdentifier, sf::Texture());
	textures[texIdentifier].loadFromFile(texturePath);
}
