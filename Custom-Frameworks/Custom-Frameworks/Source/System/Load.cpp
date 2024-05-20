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
	textures.emplace(std::piecewise_construct, std::forward_as_tuple(texIdentifier), std::forward_as_tuple());
	textures.at(texIdentifier).loadFromFile(texturePath);
}

sf::Texture const& Load::Assets::getTexture(std::string const& texIdentifier) const {
	return textures.at(texIdentifier);
}

// ================================================================================
// Function: Load Font Member Function
// ================================================================================

void Load::Assets::loadFontFromFile(std::string const& fontIdentifier, std::string const& fontPath) {
	fonts.emplace(std::piecewise_construct, std::forward_as_tuple(fontIdentifier), std::forward_as_tuple());
	fonts.at(fontIdentifier).loadFromFile(fontPath);
}

sf::Font const& Load::Assets::getFont(std::string const& fontIdentifier) const {
	return fonts.at(fontIdentifier);
}

void Load::Assets::setPrimaryFont(std::string const& fontIdentifier) {
	primaryFont = fonts.at(fontIdentifier);
}

void Load::Assets::setSecondaryFont(std::string const& fontIdentifier) {
	secondaryFont = fonts.at(fontIdentifier);
}

sf::Font const& Load::Assets::getPrimaryFont() const {
	return primaryFont;
}

sf::Font const& Load::Assets::getSecondaryFont() const {
	return secondaryFont;
}