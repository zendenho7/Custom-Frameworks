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
	const float HOVER_SCALE = 1.05f;	//Percentage Of Button Size
	const float HOVER_TIME = 0.25f;		//Hover Time In Seconds

	//Button Interface
	class RectButton : public Drawables::D_RoundedRectangle {
	private:
		//Hovering Operators
		bool b_hoverEnabled;
		float hoverScale;
		float hoverDuration;

		//Button Display Text
		std::string btnTxt;

		//Hover Operations
		void hoverButton();
		void normalButton();
	public:

		//Constructors
		RectButton() = default;
		RectButton(sf::Color const& color, std::string const& text, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hover = true);

		//Set Custom Hover Scale & Duration
		void setHoverSettings(bool hover, float scale, float duration);

		//Set Button Text
		void setButtonText(std::string const& text);
		std::string const& getButtonText() const;

		//Button Click Check
		bool isButtonClicked();
	};
}

#endif // !USERINTERFACE_HPP
