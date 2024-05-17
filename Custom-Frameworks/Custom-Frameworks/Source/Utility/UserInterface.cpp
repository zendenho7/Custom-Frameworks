/*****************************************************************************************************************
@file         UserInterface.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for the defintion of user interface classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"

// ================================================================================
// Class: Rect Button
// ================================================================================

Interface::RectButton::RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hover)
	: b_hoverEnabled{ hover }, b_hoverInProgress{ false }, hoverScale{ BTN_HOVER_SCALE }, hoverDuration{ BTN_HOVER_TIME }, textToBtnRatio{ 0.0f, 0.0f }, D_Rect(color, size, pos, rounding, rotation, oPos), D_Text()
{
}

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

void Interface::RectButton::setHoverSettings(bool hover, sf::Vector2f const& scale, float duration) {
	b_hoverEnabled = hover;
	b_hoverInProgress = false;
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

void Interface::RectButton::setPosition(sf::Vector2f const& pos) {
	D_Rect.setPosition(pos);
	D_Text.setPosition(pos);
}

sf::Vector2f Interface::RectButton::getPosition() const {
	return D_Rect.getGlobalBounds().getPosition() + D_Rect.getOrigin();
}

void Interface::RectButton::setScale(sf::Vector2f const& scale) {
	D_Rect.setScale(scale);
	D_Rect.Custom_SetFixedScale();
	D_Text.setScale(scale);
	D_Text.Custom_SetFixedScale();
}

sf::FloatRect Interface::RectButton::getLocalBounds() const {
	return D_Rect.getLocalBounds();
}

sf::FloatRect Interface::RectButton::getGlobalBounds() const {
	return D_Rect.getGlobalBounds();
}

bool Interface::RectButton::getHoverStatus() const {
	return b_hoverInProgress;
}

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
			b_hoverInProgress = true;
		}

		//Check For Mouse Click
		if (exEvents->mouseTriggered(sf::Mouse::Left)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		b_hoverInProgress = false;
	}

	//Return Button Back To Origin State
	if(D_Rect.getScale().x > D_Rect.Custom_GetFixedScale().x && D_Rect.getScale().y > D_Rect.Custom_GetFixedScale().y)
	normalButton();

	return false;
}

void Interface::RectButton::Custom_Draw() const {

	//Draw Rect Button
	D_Rect.Custom_Draw();

	//Draw BtnTxt If Text Is Present
	if (!D_Text.getString().isEmpty()) {
		D_Text.Custom_Draw();
	}
}

// ================================================================================
// Class: DropDown
// ================================================================================

Interface::DropDown::DropDown(sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownType type, DropDownAlign alignment
)
	: b_DropDownHidden{ true }, b_MouseOverDropDown{ false }, alignmentStyle{ alignment }, dropDownType{ type }, b_ArrangeVertical{ false },
	dropDownBtn(btncolor, btnsize, btnpos, rounding), dropDownContainer(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding)
{
	switch (alignmentStyle) {
	case DropDownAlign::DOWN_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	default:
		break;
	}
}

void Interface::DropDown::addComponents(std::string const& identifier) {
	dropDownButtons.emplace(identifier, RectButton());
}

void Interface::DropDown::arrangeComponents() {

}

void Interface::DropDown::Custom_Update() {

	//Update DropDown
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Get DropDown Bound & Size
	sf::FloatRect buttonObj = dropDownContainer.getGlobalBounds();

	//Check For Mouse Click Within DropDown Bounds
	if (mousePos.x > (buttonObj.left) && //Left Side
		mousePos.x < (buttonObj.left + buttonObj.width) && //Right Side
		mousePos.y >(buttonObj.top) && //Top Side
		mousePos.y < (buttonObj.top + buttonObj.height)) //Bottom Side
	{
		b_MouseOverDropDown = true;
	}
	else {
		b_MouseOverDropDown = false;
	}

	//Update DropDown Based On DropDown Type
	switch (dropDownType) {
	case DropDownType::HOVER:
		//Update Button
		dropDownBtn.isButtonClicked();

		//Show Or Hide DropDown
		if (dropDownBtn.getHoverStatus()) {
			b_DropDownHidden = false;
		}
		else {
			if (!b_MouseOverDropDown) {
				b_DropDownHidden = true;
			}
		}
		break;
	case DropDownType::CLICK:
		if (dropDownBtn.isButtonClicked()) {
			b_DropDownHidden = !b_DropDownHidden;
		}
		break;
	default:
		break;
	}
}

void Interface::DropDown::Custom_Draw() {
	//Draw DropDown Container
	dropDownBtn.Custom_Draw();

	if (!b_DropDownHidden) {
		exEvents->window.draw(dropDownContainer);
	}
}
