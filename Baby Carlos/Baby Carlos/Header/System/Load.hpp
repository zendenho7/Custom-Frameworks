/*****************************************************************************************************************
@file         Load.hpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This is the header file for all assets loading functionalities in the application

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef LOAD_HPP
#define LOAD_HPP

namespace Load {

	// ================================================================================
	// Class: Assets Load Handler
	// ================================================================================
	class Assets {
	public:
		// <Type Of Texture, Loaded Texture>
		std::map<std::string, sf::Texture> textures;

		// <Type Of Sound, Loaded Sound>
		std::map<std::string, sf::Sound> audios;

		//Constructor
		Assets(){}

		//Add Texture Overload
		void addTexFromFile(std::string const& texIdentifier, std::string const& texturePath);
	};
}

// ================================================================================
// External Load Assets Handler
// ================================================================================

extern Load::Assets* exAssets;

#endif // !LOAD_HPP
