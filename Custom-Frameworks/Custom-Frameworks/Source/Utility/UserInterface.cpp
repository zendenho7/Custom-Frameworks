/*****************************************************************************************************************
@file         UserInterface.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for the defintion of user interface classes & objects

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"
#include "..\..\Header\Utility\Collision.hpp"

// ================================================================================
// Class: Rect Button
// ================================================================================

Interface::RectButton::RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hoverAnimation)
	: btnBase(color, size, pos, rounding, rotation, oPos), btnTxt(), b_HoverAnimationEnabled{ hoverAnimation }, b_Hovering{ false }, hoverScale{ BTN_HOVER_SCALE }, hoverDuration{ BTN_HOVER_TIME }, textToBtnRatio{ 0.0f, 0.0f }
{
}

void Interface::RectButton::setRectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hoverAnimation)
{
	btnBase.setD_RoundedRectangle(color, size, pos, rounding, rotation, oPos);
	b_HoverAnimationEnabled = hoverAnimation;
	b_Hovering = false;
	hoverScale = BTN_HOVER_SCALE;
	hoverDuration = BTN_HOVER_TIME;
	textToBtnRatio = { 0.0f, 0.0f };
}

void Interface::RectButton::hoverButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((btnBase.Custom_GetFixedScale().x * hoverScale.x) - btnBase.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()), ((btnBase.Custom_GetFixedScale().y * hoverScale.y) - btnBase.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };
	sf::Vector2f txtHoverSpeed{ ((btnTxt.Custom_GetFixedScale().x * hoverScale.x) - btnTxt.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()),  ((btnTxt.Custom_GetFixedScale().y * hoverScale.y) - btnTxt.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };

	//Hovering Scaling Up Operations
	btnBase.setScale(std::clamp(btnBase.getScale().x + btnHoverSpeed.x, btnBase.Custom_GetFixedScale().x, btnBase.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnBase.getScale().y + btnHoverSpeed.y, btnBase.Custom_GetFixedScale().y, btnBase.Custom_GetFixedScale().y * hoverScale.y));
	btnTxt.setScale(std::clamp(btnTxt.getScale().x + txtHoverSpeed.x, btnTxt.Custom_GetFixedScale().x, btnTxt.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnTxt.getScale().y + txtHoverSpeed.y, btnTxt.Custom_GetFixedScale().y, btnTxt.Custom_GetFixedScale().y * hoverScale.y));
}

void Interface::RectButton::normalButton() {
	//Hovering Speed Based On HoverTime
	sf::Vector2f btnHoverSpeed{ ((btnBase.Custom_GetFixedScale().x * hoverScale.x) - btnBase.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()), ((btnBase.Custom_GetFixedScale().y * hoverScale.y) - btnBase.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };
	sf::Vector2f txtHoverSpeed{ ((btnTxt.Custom_GetFixedScale().x * hoverScale.x) - btnTxt.Custom_GetFixedScale().x) / (hoverDuration / exTime->getDeltaTime()),  ((btnTxt.Custom_GetFixedScale().y * hoverScale.y) - btnTxt.Custom_GetFixedScale().y) / (hoverDuration / exTime->getDeltaTime()) };

	//Hovering Scaling Down Operations
	btnBase.setScale(std::clamp(btnBase.getScale().x - btnHoverSpeed.x, btnBase.Custom_GetFixedScale().x, btnBase.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnBase.getScale().y - btnHoverSpeed.y, btnBase.Custom_GetFixedScale().y, btnBase.Custom_GetFixedScale().y * hoverScale.y));
	btnTxt.setScale(std::clamp(btnTxt.getScale().x - txtHoverSpeed.x, btnTxt.Custom_GetFixedScale().x, btnTxt.Custom_GetFixedScale().x * hoverScale.x), std::clamp(btnTxt.getScale().y - txtHoverSpeed.y, btnTxt.Custom_GetFixedScale().y, btnTxt.Custom_GetFixedScale().y * hoverScale.y));
}

bool Interface::RectButton::getHoverStatus() const {
	return b_Hovering;
}

bool Interface::RectButton::isButtonClicked() {

	//Check For Mouse Click Within Bounds
	if (UI_Collision::Rect_Button(btnBase.getGlobalBounds()))
	{
		//Hover Button
		if (b_HoverAnimationEnabled) {
			hoverButton();
		}

		b_Hovering = true;

		//Check For Mouse Click
		if (exEvents->mouseTriggered(sf::Mouse::Left)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		b_Hovering = false;
	}

	//Return Button Back To Origin State
	if (btnBase.getScale().x > btnBase.Custom_GetFixedScale().x && btnBase.getScale().y > btnBase.Custom_GetFixedScale().y)
		normalButton();

	return false;
}

void Interface::RectButton::rescaleTxt() {
	//Calculate Scale
	sf::Vector2f txtratio{ btnTxt.getLocalBounds().getSize().x / btnBase.getGlobalBounds().getSize().x, btnTxt.getLocalBounds().getSize().y / btnBase.getGlobalBounds().getSize().y };
	float maxScale{ std::min(btnBase.getGlobalBounds().getSize().x / btnTxt.getLocalBounds().getSize().x, btnBase.getGlobalBounds().getSize().y / btnTxt.getLocalBounds().getSize().y) };
	float txtscale{ txtratio.x - textToBtnRatio.x > txtratio.y - textToBtnRatio.y
		? std::clamp((btnBase.getGlobalBounds().getSize().x * textToBtnRatio.x) / btnTxt.getLocalBounds().getSize().x, 0.0f, maxScale)
		: std::clamp((btnBase.getGlobalBounds().getSize().y * textToBtnRatio.y) / btnTxt.getLocalBounds().getSize().y, 0.0f, maxScale) };

	//Set Scale
	btnTxt.setScale(txtscale, txtscale);
	btnTxt.Custom_SetFixedScale();
}

void Interface::RectButton::setHoverSettings(bool hoverAnimation, sf::Vector2f const& scale, float duration) {
	b_HoverAnimationEnabled = hoverAnimation;
	b_Hovering = false;
	hoverScale = scale;
	hoverDuration = duration;
}

void Interface::RectButton::setTextToButtonRatio(sf::Vector2f const& ratio) {
	textToBtnRatio = ratio;

	rescaleTxt();
}

void Interface::RectButton::setRectButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio, sf::Uint8 charSize, Drawables::Origin oPos) {
	
	//Set Txt Ratio
	textToBtnRatio = txtBtnRatio;

	//Init Text
	btnTxt.setFont(font);
	btnTxt.setString(txt);
	btnTxt.setCharacterSize(charSize);
	btnTxt.setFillColor(color);

	//Calculate Scale
	rescaleTxt();

	//Set Based On Btn Attributes
	btnTxt.setPosition(btnBase.getPosition());
	btnTxt.setRotation(btnBase.getRotation());

	//Offset To Center Of Bounding Box
	btnTxt.Custom_OffsetToCenter();

	//Set Origin Of Rect
	btnTxt.Custom_SetOrigin(oPos);
}

void Interface::RectButton::setPosition(sf::Vector2f const& pos) {
	btnBase.setPosition(pos);
	btnTxt.setPosition(pos);
	btnTxt.Custom_OffsetToCenter();
}

sf::Vector2f Interface::RectButton::getPosition() const {
	return btnBase.Custom_GetOriginPosition();
}

void Interface::RectButton::setSize(sf::Vector2f const& size) {
	btnBase.setSize(size);
	btnBase.Custom_SetOrigin();

	rescaleTxt();
}

sf::Vector2f Interface::RectButton::getSize() const {
	return btnBase.getSize();
}

void Interface::RectButton::setScale(sf::Vector2f const& scale) {
	btnBase.setScale(scale);
	btnBase.Custom_SetFixedScale();

	rescaleTxt();
}

sf::Vector2f Interface::RectButton::getScale() const {
	return btnBase.getScale();
}

sf::FloatRect Interface::RectButton::getLocalBounds() const {
	return btnBase.getLocalBounds();
}

sf::FloatRect Interface::RectButton::getGlobalBounds() const {
	return btnBase.getGlobalBounds();
}

void Interface::RectButton::setButtonColor(sf::Color const& color) {
	btnBase.setFillColor(color);
}

sf::Color Interface::RectButton::getButtonColor() const {
	return btnBase.getFillColor();
}

void Interface::RectButton::setTxtColor(sf::Color const& color) {
	btnBase.setFillColor(color);
}

sf::Color Interface::RectButton::getTxtColor() const {
	return btnTxt.getFillColor();
}

void Interface::RectButton::setButtonRounding(float rounding) {
	btnBase.setCornerRounding(rounding);
}

float Interface::RectButton::getButtonRounding() const {
	return btnBase.getCornerRounding();
}

void Interface::RectButton::Custom_Draw() const {

	//Draw Rect Button
	btnBase.Custom_Draw();

	//Draw BtnTxt If Text Is Present
	if (!btnTxt.getString().isEmpty()) {
		btnTxt.Custom_Draw();
	}
}

std::string Interface::RectButton::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << btnBase.serialize() << " " << btnTxt.serialize() << " "
		<< b_HoverAnimationEnabled << " " << b_Hovering << " " << hoverDuration << " "
		<< hoverScale.x << " " << hoverScale.y << " " << textToBtnRatio.x << " " << textToBtnRatio.y;

	return oss.str();
}

void Interface::RectButton::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Input Stream From String
	btnBase.deserialize(iss);
	btnTxt.deserialize(iss) 
		>> b_HoverAnimationEnabled >> b_Hovering >> hoverDuration
		>> hoverScale.x >> hoverScale.y >> textToBtnRatio.x >> textToBtnRatio.y;
}

std::istringstream& Interface::RectButton::deserialize(std::istringstream& stream) {

	//Input Stream From String
	btnBase.deserialize(stream);
	btnTxt.deserialize(stream)
		>> b_HoverAnimationEnabled >> b_Hovering >> hoverDuration
		>> hoverScale.x >> hoverScale.y >> textToBtnRatio.x >> textToBtnRatio.y;

	return stream;
}

// ================================================================================
// Class: DropDown
// ================================================================================

Interface::DropDown::DropDown(std::string const& btntxt, sf::Color const& btntxtcolor, sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownBtnType type, DropDownAlign alignment)
	: dropDownBtn(btncolor, btnsize, btnpos, rounding, 0.0f, Drawables::Origin::CENTER, false), dropDownContainer(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding),
	b_DropDownHidden{ true }, b_MouseOverDropDown{ false }, alignmentStyle{ alignment }, buttonType{ type }
{
	//Init DropDown Button text
	dropDownBtn.setRectButtonText(btntxt, exAssets->getPrimaryFont(), btntxtcolor);

	//Set Position Of DropDown Container
	switch (alignmentStyle) {
	case DropDownAlign::DOWN_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	default:
		break;
	}
}

void Interface::DropDown::setDropDown(std::string const& btntxt, sf::Color const& btntxtcolor, sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownBtnType type, DropDownAlign alignment)
{
	alignmentStyle = alignment;
	buttonType = type;
	dropDownBtn.setRectButton(btncolor, btnsize, btnpos, rounding, 0.0f, Drawables::Origin::CENTER, false);
	dropDownContainer.setD_RoundedRectangle(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding);
	//Init DropDown Button text
	dropDownBtn.setRectButtonText(btntxt, exAssets->getPrimaryFont(), btntxtcolor);

	//Set Position Of DropDown Container
	switch (alignmentStyle) {
	case DropDownAlign::DOWN_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_CENTER:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_LEFT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_RIGHT:
		dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 2), dropDownBtn.getPosition().y - (dropDownBtn.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	default:
		break;
	}
}

void Interface::DropDown::addButtons(std::string const& identifier, sf::Color const& btnColor, sf::Color const& txtColor, bool usePrimaryFont) {
	dropDownButtonsKey.emplace_back(identifier);
	dropDownButtons.emplace(std::piecewise_construct, std::forward_as_tuple(dropDownButtonsKey[dropDownButtonsKey.size() - 1]), std::forward_as_tuple(btnColor, sf::Vector2f(), sf::Vector2f()));
	dropDownButtons[dropDownButtonsKey[dropDownButtonsKey.size() - 1]].setRectButtonText(dropDownButtonsKey[dropDownButtonsKey.size() - 1], usePrimaryFont ? exAssets->getPrimaryFont() : exAssets->getSecondaryFont(), txtColor);
}

void Interface::DropDown::arrangeButtons(sf::Vector2f const& padding, float spaceBetweenButtons, float buttonRounding, DropDownArrangement arrangementStyle) {

	//Area Left To Occup After Accounting For Padding
	sf::Vector2f workableArea{ dropDownContainer.getGlobalBounds().getSize() - padding - padding };
	float totalSpace{ spaceBetweenButtons * (dropDownButtonsKey.size() - 1) };

	sf::Vector2f startpos;
	sf::Vector2f btnSize;

	switch (arrangementStyle) {
	case DropDownArrangement::VERTICAL:
		btnSize = { workableArea.x, (workableArea.y - totalSpace) / dropDownButtonsKey.size() };
		startpos = { dropDownContainer.Custom_GetOriginPosition().x, dropDownContainer.Custom_GetOriginPosition().y - (workableArea.y / 2) + (btnSize.y / 2)};
		for (std::string const& key : dropDownButtonsKey) {
			dropDownButtons[key].setSize(btnSize);
			dropDownButtons[key].setPosition(startpos);
			dropDownButtons[key].setButtonRounding(buttonRounding);
			(startpos.y += btnSize.y) += spaceBetweenButtons;
		}
		break;
	case DropDownArrangement::HORIZONTAL:
		btnSize = { (workableArea.x - totalSpace) / dropDownButtonsKey.size(), workableArea.y };
		startpos = { dropDownContainer.Custom_GetOriginPosition().x - (workableArea.x / 2) + (btnSize.x / 2), dropDownContainer.Custom_GetOriginPosition().x };
		for (std::string const& key : dropDownButtonsKey) {
			dropDownButtons[key].setSize(btnSize);
			dropDownButtons[key].setPosition(startpos);
			dropDownButtons[key].setButtonRounding(buttonRounding);
			(startpos.x += btnSize.x) += spaceBetweenButtons;
		}
		break;
	default:
		break;
	}
}

bool Interface::DropDown::isButtonClicked(std::string const& identifier) {
	return !b_DropDownHidden ? dropDownButtons.at(identifier).isButtonClicked() : false;
}

void Interface::DropDown::updateDropDown() {

	if (!b_DropDownHidden) {

		//Check For Mouse Click Within DropDown Bounds
		if (UI_Collision::Rect_Button(dropDownContainer.getGlobalBounds()))
		{
			//Set Mouse Over DropDown To True
			b_MouseOverDropDown = true;
		}
		else {
			//Set Mouse Over DropDown To False
			b_MouseOverDropDown = false;
		}
	}

	//Update DropDown Based On DropDown Type
	switch (buttonType) {
	case DropDownBtnType::HOVER:
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
	case DropDownBtnType::CLICK:
		if (dropDownBtn.isButtonClicked()) {
			b_DropDownHidden = !b_DropDownHidden;
		}
		break;
	default:
		break;
	}
}

void Interface::DropDown::drawDropDown() {
	//Draw DropDown Btn Activator
	dropDownBtn.Custom_Draw();

	//Draw Container & Buttons If DropDown Is Shown
	if (!b_DropDownHidden) {
		exEvents->window.draw(dropDownContainer);

		//Draw Buttons
		for (std::string const& key : dropDownButtonsKey) {
			dropDownButtons[key].Custom_Draw();
		}
	}
}

std::string Interface::DropDown::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << dropDownBtn.serialize() << " " << dropDownContainer.serialize() << " "
		<< b_DropDownHidden << " " << b_MouseOverDropDown << " "
		<< static_cast<int>(buttonType) << " " << static_cast<int>(alignmentStyle) << " ";

	for (std::string const& key : dropDownButtonsKey) {
		oss << key << " " << dropDownButtons.at(key).serialize() << " ";
	}

	return oss.str();
}

void Interface::DropDown::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	int btntype;
	int alignstyle;

	//Output Stream From String
	dropDownBtn.deserialize(iss);
	dropDownContainer.deserialize(iss)
		>> b_DropDownHidden >> b_MouseOverDropDown
		>> btntype >> alignstyle;

	buttonType = static_cast<DropDownBtnType>(btntype);
	alignmentStyle = static_cast<DropDownAlign>(alignstyle);

	for (std::string& key : dropDownButtonsKey) {
		iss >> key;
		dropDownButtons.at(key).deserialize(iss);
	}
}

std::istringstream& Interface::DropDown::deserialize(std::istringstream& stream) {
	//Temporary Variables
	int btntype;
	int alignstyle;

	//Output Stream From String
	dropDownBtn.deserialize(stream);
	dropDownContainer.deserialize(stream)
		>> b_DropDownHidden >> b_MouseOverDropDown
		>> btntype >> alignstyle;

	buttonType = static_cast<DropDownBtnType>(btntype);
	alignmentStyle = static_cast<DropDownAlign>(alignstyle);

	for (std::string& key : dropDownButtonsKey) {
		stream >> key;
		dropDownButtons.at(key).deserialize(stream);
	}

	return stream;
}
