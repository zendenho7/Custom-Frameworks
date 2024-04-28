/*****************************************************************************************************************
@file         Load.hpp
@project      Pathfinding Algorithms
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
		std::unordered_map<std::string, sf::Texture> textures;

		// <Type Of Font, Loaded Font>
		std::unordered_map<std::string, sf::Font> fonts;

		// <Type Of Sound, Loaded Sound>
		std::unordered_map<std::string, sf::Sound> audios;

		//Constructor
		Assets() = default;

		//Load Textures
		void loadTexFromFile(std::string const& texIdentifier, std::string const& texturePath);

		//Load Fonts
		void loadFontFromFile(std::string const& fontIdentifier, std::string const& fontPath);
	};
}

#endif // !LOAD_HPP
