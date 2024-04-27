/*****************************************************************************************************************
@file         UserInterface.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for the defintion of user interface classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

// ================================================================================
// Class: Rect Button Constructor
// ================================================================================

Interface::RectButton::RectButton(sf::Color const& color, std::string const& text, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Drawables::Origin oPos, bool hover)
	: btnTxt{ text }, b_hoverEnabled { hover }, hoverScale{ HOVER_SCALE }, hoverDuration{ HOVER_TIME }, drawable() 
{
	Drawables::initRectShape(drawable, color, size, pos, rotation, oPos);
}

// ================================================================================
// Class: Rect Button Private Hover Operations
// ================================================================================

void Interface::RectButton::hoverButton() {
	//Hovering Speed Based On HoverTime
	float hoverSpeed{ (hoverScale - 1.0f) / (hoverDuration / exTime->deltaTime) };

	//Hovering Scaling Up Operations
	drawable.setScale((drawable.getScale().x < hoverScale ? drawable.getScale().x + hoverSpeed : drawable.getScale().x), (drawable.getScale().y < hoverScale ? drawable.getScale().y + hoverSpeed : drawable.getScale().y));
}

void Interface::RectButton::normalButton() {
	//Hovering Speed Based On HoverTime
	float hoverSpeed{ (hoverScale - 1.0f) / (hoverDuration / exTime->deltaTime) };

	//Hovering Scaling Down Operations
	drawable.setScale((drawable.getScale().x > 1.0f ? drawable.getScale().x - hoverSpeed : drawable.getScale().x), (drawable.getScale().y > 1.0f ? drawable.getScale().y - hoverSpeed : drawable.getScale().y));
}

// ================================================================================
// Class: Rect Button Getters
// ================================================================================

std::string const& Interface::RectButton::getButtonText() const{
	return btnTxt;
}

// ================================================================================
// Class: Rect Button Setters
// ================================================================================

void Interface::RectButton::setHoverSettings(bool hover, float scale, float duration) {
	b_hoverEnabled = hover;
	hoverScale = scale;
	hoverDuration = duration;
}

void Interface::RectButton::setButtonText(std::string const& text) {
	btnTxt = text;
}

// ================================================================================
// Class: Rect Button Hover & Clicked Check
// ================================================================================

bool Interface::RectButton::isButtonClicked() {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get Button Bound & Size
	sf::FloatRect buttonObj = drawable.getGlobalBounds();

	//Check For Mouse Click Within Bounds
	if (mousePos.x > (buttonObj.left) && //Left Side
		mousePos.x < (buttonObj.left + buttonObj.width) && //Right Side
		mousePos.y > (buttonObj.top) && //Top Side
		mousePos.y < (buttonObj.top + buttonObj.height)) //Bottom Side
	{
		//Hover Button
		if (b_hoverEnabled) {
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

	//Return Button Back To Origin State
	if(drawable.getScale().x > 1.0f && drawable.getScale().y > 1.0f)
	normalButton();

	return false;
}
