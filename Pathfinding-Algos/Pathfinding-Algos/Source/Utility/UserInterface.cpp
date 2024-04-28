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

Interface::RectButton::RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hover)
	: D_RoundedRectangle(color, size, pos, rounding, rotation, oPos), btnTxt(), b_hoverEnabled{hover}, hoverScale{HOVER_SCALE}, hoverDuration{HOVER_TIME}
{
}

// ================================================================================
// Class: Rect Button Private Hover Operations
// ================================================================================

void Interface::RectButton::hoverButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((Custom_GetFixedScale().x * hoverScale.x) - Custom_GetFixedScale().x) / (hoverDuration / exTime->deltaTime), ((Custom_GetFixedScale().y * hoverScale.y) - Custom_GetFixedScale().y) / (hoverDuration / exTime->deltaTime) };
	sf::Vector2f txtHoverSpeed{ ((btnTxt.Custom_GetFixedScale().x * hoverScale.x) - btnTxt.Custom_GetFixedScale().x) / (hoverDuration / exTime->deltaTime),  ((btnTxt.Custom_GetFixedScale().y * hoverScale.y) - btnTxt.Custom_GetFixedScale().y) / (hoverDuration / exTime->deltaTime) };

	//Hovering Scaling Up Operations
	setScale(std::clamp(getScale().x + btnHoverSpeed.x, Custom_GetFixedScale().x, Custom_GetFixedScale().x * hoverScale.x), std::clamp(getScale().x + btnHoverSpeed.x, Custom_GetFixedScale().y, Custom_GetFixedScale().y * hoverScale.y));
	btnTxt.setScale(std::clamp(btnTxt.getScale().x + txtHoverSpeed.x, btnTxt.Custom_GetFixedScale().x, btnTxt.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnTxt.getScale().y + txtHoverSpeed.y, btnTxt.Custom_GetFixedScale().y, btnTxt.Custom_GetFixedScale().y * hoverScale.y));
}

void Interface::RectButton::normalButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((Custom_GetFixedScale().x * hoverScale.x) - Custom_GetFixedScale().x) / (hoverDuration / exTime->deltaTime), ((Custom_GetFixedScale().y * hoverScale.y) - Custom_GetFixedScale().y) / (hoverDuration / exTime->deltaTime) };
	sf::Vector2f txtHoverSpeed{ ((btnTxt.Custom_GetFixedScale().x * hoverScale.x) - btnTxt.Custom_GetFixedScale().x) / (hoverDuration / exTime->deltaTime),  ((btnTxt.Custom_GetFixedScale().y * hoverScale.y) - btnTxt.Custom_GetFixedScale().y) / (hoverDuration / exTime->deltaTime) };

	//Hovering Scaling Down Operations
	setScale(std::clamp(getScale().x - btnHoverSpeed.x, Custom_GetFixedScale().x, Custom_GetFixedScale().x * hoverScale.x), std::clamp(getScale().x - btnHoverSpeed.x, Custom_GetFixedScale().y, Custom_GetFixedScale().y * hoverScale.y));
	btnTxt.setScale(std::clamp(btnTxt.getScale().x - txtHoverSpeed.x, btnTxt.Custom_GetFixedScale().x, btnTxt.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnTxt.getScale().y - txtHoverSpeed.y, btnTxt.Custom_GetFixedScale().y, btnTxt.Custom_GetFixedScale().y * hoverScale.y));
}

// ================================================================================
// Class: Rect Button Getters
// ================================================================================

Drawables::D_Text& Interface::RectButton::getButtonText() {
	return btnTxt;
}

// ================================================================================
// Class: Rect Button Setters
// ================================================================================

void Interface::RectButton::setHoverSettings(bool hover, sf::Vector2f const& scale, float duration) {
	b_hoverEnabled = hover;
	hoverScale = scale;
	hoverDuration = duration;
}

void Interface::RectButton::initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Uint8 charSize, Drawables::Origin oPos) {
	
	//Init Text
	btnTxt.setFont(font);
	btnTxt.setString(txt);
	btnTxt.setCharacterSize(charSize);
	btnTxt.setFillColor(color);

	//Set Based On Btn Attributes
	btnTxt.setPosition(getPosition());
	btnTxt.setRotation(getRotation());

	//Set Origin Of Rect
	btnTxt.Custom_SetOrigin(oPos);
}

void Interface::RectButton::setButtonText(std::string const& txt) {
	 btnTxt.setString(txt);
}

// ================================================================================
// Class: Rect Button Hover & Clicked Check
// ================================================================================

bool Interface::RectButton::isButtonClicked() {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get Button Bound & Size
	sf::FloatRect buttonObj = getGlobalBounds();

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
	if(getScale().x > 1.0f && getScale().y > 1.0f)
	normalButton();

	return false;
}
