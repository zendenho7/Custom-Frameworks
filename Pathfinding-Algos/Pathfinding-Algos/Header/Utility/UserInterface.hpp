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
	const sf::Vector2f	DEF_TXT_TO_BTN_RATIO{ 0.5f, 0.5f };

	//Button Interface
	class RectButton {
	private:
		//Hovering Operators
		bool b_hoverEnabled;
		sf::Vector2f hoverScale;
		float hoverDuration;

		//Text To Button Ratio ( Text Will Fit Within This Ratio )
		sf::Vector2f textToBtnRatio;

		//Hover Operations
		void hoverButton();
		void normalButton();
	public:

		//Rect Drawable
		Drawables::D_RoundedRectangle D_Rect;

		//Text Drawable
		Drawables::D_Text D_Text;

		//Constructors
		RectButton() = default;
		RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hover = true);

		//Set Custom Hover Scale & Duration
		void setHoverSettings(bool hover, sf::Vector2f const& scale, float duration);

		//Initialize Button Text
		void initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio = DEF_TXT_TO_BTN_RATIO, sf::Uint8 charSize = Drawables::DEF_CHAR_SIZE, Drawables::Origin oPos = Drawables::Origin::CENTER);

		//Set Text To Button Ratio ( Text Will Be Fit Within This Ratio )
		void setTextToButtonRatio(sf::Vector2f const& ratio);

		//Button Click Check
		bool isButtonClicked();

		//Draw Button Onto Render Target
		void drawButton();
	};
}

#endif // !USERINTERFACE_HPP
