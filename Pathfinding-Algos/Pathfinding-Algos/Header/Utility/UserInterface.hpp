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

#include "..\..\Header\Utility\Entity.hpp"
#include "..\..\Header\Utility\Utils.hpp"

namespace Interface {

	//Interface Default Constants
	const float HOVER_SCALE = 1.05f;	//Percentage Of Button Size
	const float HOVER_TIME = 0.25f;		//Hover Time In Seconds

	//Button Interface
	class RectButton : public Entity::rect {
	private:
		//Hovering Operators
		bool b_hoverEnabled;
		float hoverScale;
		float hoverDuration;

		//Hover Operations
		void hoverButton();
		void normalButton();
	public:
		//Constructors
		RectButton() = default;
		RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Entity::Origin oPos = Entity::Origin::CENTER, bool hover = true);

		//Set Custom Hover Scale & Duration
		void setCustomHover(float scale, float duration);

		//Button Click Check
		bool isButtonClicked();
	};
}

#endif // !USERINTERFACE_HPP
