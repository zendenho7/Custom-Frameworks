/*****************************************************************************************************************
@file         Load.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains all the defintions of loading functionalities in the project

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Load.hpp"

// ================================================================================
// Function: Load Assets Constructor
// ================================================================================

// ================================================================================
// Function: Load Texture Member Function
// ================================================================================

void Load::Assets::loadTexFromFile(std::string const& texIdentifier, std::string const& texturePath) {
	textures.emplace(texIdentifier, sf::Texture());
	textures[texIdentifier].loadFromFile(texturePath);
}

// ================================================================================
// Function: Load Font Member Function
// ================================================================================

void Load::Assets::loadFontFromFile(std::string const& fontIdentifier, std::string const& fontPath) {
	fonts.emplace(fontIdentifier, sf::Font());
	fonts[fontIdentifier].loadFromFile(fontPath);
}