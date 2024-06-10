/*****************************************************************************************************************
@file         Load.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file for all assets loading functionalities in the application

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef LOAD_HPP
#define LOAD_HPP

namespace Load {

	// ================================================================================
	// Class: Assets Load Handler
	// ================================================================================

	class Assets {
	private:
		//Main Fonts To Use
		sf::Font primaryFont;
		sf::Font secondaryFont;

		// <Type Of Texture, Loaded Texture>
		std::unordered_map<std::string, sf::Texture> textures;

		// <Type Of Font, Loaded Font>
		std::unordered_map<std::string, sf::Font> fonts;

		// <Type Of Sound, Loaded Sound>
		std::unordered_map<std::string, sf::Sound> audios;
	public:

		//Default Constructor
		Assets() = default;

		/// <summary>
		/// Load Texture From File
		/// </summary>
		/// <param name="texIdentifier">: String Identifier For Unordered Map</param>
		/// <param name="texturePath">: File Path To Texture</param>
		void loadTexFromFile(std::string const& texIdentifier, std::string const& texturePath);

		sf::Texture const& getTexture(std::string const& texIdentifier) const;

		/// <summary>
		/// Load Font From File
		/// </summary>
		/// <param name="fontIdentifier">: String Identifier For Unordered Map</param>
		/// <param name="fontPath">: File Path To Font</param>
		void loadFontFromFile(std::string const& fontIdentifier, std::string const& fontPath);

		//Get Font
		sf::Font const& getFont(std::string const& fontIdentifier) const;

		//Set Primary Font
		void setPrimaryFont(std::string const& fontIdentifier);

		//Set Secondary Font
		void setSecondaryFont(std::string const& fontIdentifier);

		//Get Primary Font
		sf::Font const& getPrimaryFont() const;

		//Get Secondary Font
		sf::Font const& getSecondaryFont() const;
	};
}

#endif // !LOAD_HPP
