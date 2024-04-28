/*****************************************************************************************************************
@file         UserInterface.hpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the header file for the user interface classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "..\..\Header\Utility\Utils.hpp"
#include "..\..\Header\Utility\Drawables.hpp"

namespace Interface {

	//Interface Default Constants
	const sf::Vector2f	HOVER_SCALE{ 1.05f, 1.05f };	//Percentage Of Button Size
	const float			HOVER_TIME{ 0.25f };		//Hover Time In Seconds

	//Button Interface
	class RectButton : public Drawables::D_RoundedRectangle {
	private:
		//Hovering Operators
		bool b_hoverEnabled;
		sf::Vector2f hoverScale;
		float hoverDuration;

		//Hover Operations
		void hoverButton();
		void normalButton();

		//Text Drawable
		Drawables::D_Text btnTxt;
	public:

		//Constructors
		RectButton() = default;
		RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hover = true);

		//Set Custom Hover Scale & Duration
		void setHoverSettings(bool hover, sf::Vector2f const& scale, float duration);

		//Initialize Button Text
		void initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Uint8 charSize = 54, Drawables::Origin oPos = Drawables::Origin::CENTER);

		//Set Button Text
		void setButtonText(std::string const& txt);
		Drawables::D_Text& getButtonText();

		//Button Click Check
		bool isButtonClicked();
	};
}

#endif // !USERINTERFACE_HPP
