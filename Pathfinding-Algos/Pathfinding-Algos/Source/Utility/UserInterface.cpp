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
	: b_hoverEnabled{ hover }, hoverScale{ HOVER_SCALE }, hoverDuration{ HOVER_TIME }, textToBtnRatio{ 0.0f, 0.0f }, D_Rect(color, size, pos, rounding, rotation, oPos), D_Text()
{
}

// ================================================================================
// Class: Rect Button Private Hover Operations
// ================================================================================

void Interface::RectButton::hoverButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((D_Rect.Custom_GetFixedScale().x * hoverScale.x) - D_Rect.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()), ((D_Rect.Custom_GetFixedScale().y * hoverScale.y) - D_Rect.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };
	sf::Vector2f txtHoverSpeed{ ((D_Text.Custom_GetFixedScale().x * hoverScale.x) - D_Text.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()),  ((D_Text.Custom_GetFixedScale().y * hoverScale.y) - D_Text.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };

	//Hovering Scaling Up Operations
	D_Rect.setScale(std::clamp(D_Rect.getScale().x + btnHoverSpeed.x, D_Rect.Custom_GetFixedScale().x, D_Rect.Custom_GetFixedScale().x * hoverScale.x), std::clamp(D_Rect.getScale().y + btnHoverSpeed.y, D_Rect.Custom_GetFixedScale().y, D_Rect.Custom_GetFixedScale().y * hoverScale.y));
	D_Text.setScale(std::clamp(D_Text.getScale().x + txtHoverSpeed.x, D_Text.Custom_GetFixedScale().x, D_Text.Custom_GetFixedScale().x * hoverScale.x), std::clamp(D_Text.getScale().y + txtHoverSpeed.y, D_Text.Custom_GetFixedScale().y, D_Text.Custom_GetFixedScale().y * hoverScale.y));
}

void Interface::RectButton::normalButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((D_Rect.Custom_GetFixedScale().x * hoverScale.x) - D_Rect.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()), ((D_Rect.Custom_GetFixedScale().y * hoverScale.y) - D_Rect.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };
	sf::Vector2f txtHoverSpeed{ ((D_Text.Custom_GetFixedScale().x * hoverScale.x) - D_Text.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()),  ((D_Text.Custom_GetFixedScale().y * hoverScale.y) - D_Text.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };

	//Hovering Scaling Down Operations
	D_Rect.setScale(std::clamp(D_Rect.getScale().x - btnHoverSpeed.x, D_Rect.Custom_GetFixedScale().x, D_Rect.Custom_GetFixedScale().x * hoverScale.x), std::clamp(D_Rect.getScale().y - btnHoverSpeed.y, D_Rect.Custom_GetFixedScale().y, D_Rect.Custom_GetFixedScale().y * hoverScale.y));
	D_Text.setScale(std::clamp(D_Text.getScale().x - txtHoverSpeed.x, D_Text.Custom_GetFixedScale().x, D_Text.Custom_GetFixedScale().x * hoverScale.x), std::clamp(D_Text.getScale().y - txtHoverSpeed.y, D_Text.Custom_GetFixedScale().y, D_Text.Custom_GetFixedScale().y * hoverScale.y));
}

// ================================================================================
// Class: Rect Button Setters
// ================================================================================

void Interface::RectButton::setHoverSettings(bool hover, sf::Vector2f const& scale, float duration) {
	b_hoverEnabled = hover;
	hoverScale = scale;
	hoverDuration = duration;
}

void Interface::RectButton::setTextToButtonRatio(sf::Vector2f const& ratio) {
	textToBtnRatio = ratio;
}

void Interface::RectButton::initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio, sf::Uint8 charSize, Drawables::Origin oPos) {
	
	//Set Txt Ratio
	textToBtnRatio = txtBtnRatio;

	//Init Text
	D_Text.setFont(font);
	D_Text.setString(txt);
	D_Text.setCharacterSize(charSize);
	D_Text.setFillColor(color);

	//Calculate Scale
	sf::Vector2f txtratio { D_Text.getLocalBounds().getSize().x / D_Rect.getLocalBounds().getSize().x, D_Text.getLocalBounds().getSize().y / D_Rect.getLocalBounds().getSize().y };
	float maxScale{ std::min(D_Rect.getLocalBounds().getSize().x / D_Text.getLocalBounds().getSize().x, D_Rect.getLocalBounds().getSize().y / D_Text.getLocalBounds().getSize().y) };
	float txtscale{ txtratio.x - textToBtnRatio.x > txtratio.y - textToBtnRatio.y 
		? std::clamp((D_Rect.getLocalBounds().getSize().x * textToBtnRatio.x) / D_Text.getLocalBounds().getSize().x, 0.0f, maxScale)
		: std::clamp((D_Rect.getLocalBounds().getSize().y * textToBtnRatio.y) / D_Text.getLocalBounds().getSize().y, 0.0f, maxScale) };

	//Set Scale
	D_Text.setScale(txtscale, txtscale);
	D_Text.Custom_SetFixedScale();

	//Set Based On Btn Attributes
	D_Text.setPosition(D_Rect.getPosition());
	D_Text.setRotation(D_Rect.getRotation());

	//Offset To Center Of Bounding Box
	D_Text.Custom_OffsetToCenter();

	//Set Origin Of Rect
	D_Text.Custom_SetOrigin(oPos);
}

// ================================================================================
// Class: Rect Button Hover & Clicked Check
// ================================================================================

bool Interface::RectButton::isButtonClicked() {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get Button Bound & Size
	sf::FloatRect buttonObj = D_Rect.getGlobalBounds();

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
	if(D_Rect.getScale().x > D_Rect.Custom_GetFixedScale().x && D_Rect.getScale().y > D_Rect.Custom_GetFixedScale().y)
	normalButton();

	return false;
}

void Interface::RectButton::drawButton() {

	//Draw Rect Button
	exEvents->window.draw(D_Rect);

	//Draw BtnTxt If Text Is Present
	if (!D_Text.getString().isEmpty()) {
		exEvents->window.draw(D_Text);
	}
}
