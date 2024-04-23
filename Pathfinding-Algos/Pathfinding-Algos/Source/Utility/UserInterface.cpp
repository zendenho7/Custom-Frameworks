/*****************************************************************************************************************
@file         UserInterface.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for the defintion of user interface classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

Interface::RectButton::RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Entity::Origin oPos, bool hover)
	: rect(color, size, pos, rotation, oPos), hoverEnabled{ hover }
{
}

void Interface::RectButton::hoverButton() {
	//Hovering Speed Based On HoverTime
	float hoverSpeed{ HOVER_SCALE / (HOVER_TIME / exTime->deltaTime) };

	//Hovering Scaling Up Operations
	d_Rect.setScale((d_Rect.getScale().x < HOVER_SCALE ? d_Rect.getScale().x + hoverSpeed : d_Rect.getScale().x), (d_Rect.getScale().y < HOVER_SCALE ? d_Rect.getScale().y + hoverSpeed : d_Rect.getScale().y));
}

void Interface::RectButton::normalButton() {
	//Hovering Speed Based On HoverTime
	float hoverSpeed{ HOVER_SCALE / (HOVER_TIME / exTime->deltaTime) };

	//Hovering Scaling Down Operations
	d_Rect.setScale((d_Rect.getScale().x > 1.0f ? d_Rect.getScale().x - hoverSpeed : d_Rect.getScale().x), (d_Rect.getScale().y > 1.0f ? d_Rect.getScale().y - hoverSpeed : d_Rect.getScale().y));
}

bool Interface::RectButton::isButtonClicked() {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get Button Bound & Size
	sf::FloatRect buttonObj = d_Rect.getGlobalBounds();

	//Check For Mouse Click Within Bounds
	if (mousePos.x > (buttonObj.left) && //Left Side
		mousePos.x < (buttonObj.left + buttonObj.width) && //Right Side
		mousePos.y > (buttonObj.top) && //Top Side
		mousePos.y < (buttonObj.top + buttonObj.height)) //Bottom Side
	{
		//Hover Button
		if (hoverEnabled) {
			hoverButton();
		}

		//Check For Mouse Click
		if (exEvents->mouseTriggered(sf::Mouse::Left)) {
			return true;
		}
		else {
			return false;
		}
	}

	normalButton();
	return false;
}