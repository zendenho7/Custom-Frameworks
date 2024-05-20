/*****************************************************************************************************************
@file         UserInterface.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for the defintion of user interface classes & objects
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\UserInterface.hpp"
#include "..\..\Header\Utility\Collision.hpp"

// ================================================================================
// Class: Rect Button
// ================================================================================

Interface::RectButton::RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hoverAnimation)
	: D_Rect(color, size, pos, rounding, rotation, oPos), D_Text(), b_HoverAnimationEnabled{ hoverAnimation }, b_Hovering{ false }, hoverScale{ BTN_HOVER_SCALE }, hoverDuration{ BTN_HOVER_TIME }, textToBtnRatio{ 0.0f, 0.0f }
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

bool Interface::RectButton::getHoverStatus() const {
	return b_Hovering;
}

bool Interface::RectButton::isButtonClicked() {

	//Check For Mouse Click Within Bounds
	if (UI_Collision::Rect_Button(D_Rect.getGlobalBounds()))
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
	if (D_Rect.getScale().x > D_Rect.Custom_GetFixedScale().x && D_Rect.getScale().y > D_Rect.Custom_GetFixedScale().y)
		normalButton();

	return false;
}

void Interface::RectButton::rescaleTxt() {
	//Calculate Scale
	sf::Vector2f txtratio{ D_Text.getLocalBounds().getSize().x / D_Rect.getGlobalBounds().getSize().x, D_Text.getLocalBounds().getSize().y / D_Rect.getGlobalBounds().getSize().y };
	float maxScale{ std::min(D_Rect.getGlobalBounds().getSize().x / D_Text.getLocalBounds().getSize().x, D_Rect.getGlobalBounds().getSize().y / D_Text.getLocalBounds().getSize().y) };
	float txtscale{ txtratio.x - textToBtnRatio.x > txtratio.y - textToBtnRatio.y
		? std::clamp((D_Rect.getGlobalBounds().getSize().x * textToBtnRatio.x) / D_Text.getLocalBounds().getSize().x, 0.0f, maxScale)
		: std::clamp((D_Rect.getGlobalBounds().getSize().y * textToBtnRatio.y) / D_Text.getLocalBounds().getSize().y, 0.0f, maxScale) };

	//Set Scale
	D_Text.setScale(txtscale, txtscale);
	D_Text.Custom_SetFixedScale();
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

void Interface::RectButton::initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio, sf::Uint8 charSize, Drawables::Origin oPos) {
	
	//Set Txt Ratio
	textToBtnRatio = txtBtnRatio;

	//Init Text
	D_Text.setFont(font);
	D_Text.setString(txt);
	D_Text.setCharacterSize(charSize);
	D_Text.setFillColor(color);

	//Calculate Scale
	rescaleTxt();

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
	D_Text.Custom_OffsetToCenter();
}

sf::Vector2f Interface::RectButton::getPosition() const {
	return D_Rect.Custom_GetOriginPosition();
}

void Interface::RectButton::setSize(sf::Vector2f const& size) {
	D_Rect.setSize(size);
	D_Rect.Custom_SetOrigin();

	rescaleTxt();
}

sf::Vector2f Interface::RectButton::getSize() const {
	return D_Rect.getSize();
}

void Interface::RectButton::setScale(sf::Vector2f const& scale) {
	D_Rect.setScale(scale);
	D_Rect.Custom_SetFixedScale();

	rescaleTxt();
}

sf::Vector2f Interface::RectButton::getScale() const {
	return D_Rect.getScale();
}

sf::FloatRect Interface::RectButton::getLocalBounds() const {
	return D_Rect.getLocalBounds();
}

sf::FloatRect Interface::RectButton::getGlobalBounds() const {
	return D_Rect.getGlobalBounds();
}

void Interface::RectButton::setButtonColor(sf::Color const& color) {
	D_Rect.setFillColor(color);
}

sf::Color Interface::RectButton::getButtonColor() const {
	return D_Rect.getFillColor();
}

void Interface::RectButton::setTxtColor(sf::Color const& color) {
	D_Rect.setFillColor(color);
}

sf::Color Interface::RectButton::getTxtColor() const {
	return D_Text.getFillColor();
}

void Interface::RectButton::setButtonRounding(float rounding) {
	D_Rect.setCornerRounding(rounding);
}

float Interface::RectButton::getButtonRounding() const {
	return D_Rect.getCornerRounding();
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

Interface::DropDown::DropDown(std::string const& btntxt, sf::Color const& btntxtcolor, sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownType type, DropDownAlign alignment)
	: b_DropDownHidden{ true }, b_MouseOverDropDown{ false }, alignmentStyle{ alignment }, buttonType{ type },
	dropDownBtn(btncolor, btnsize, btnpos, rounding, 0.0f, Drawables::Origin::CENTER, false), dropDownContainer(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding)
{
	//Init DropDown Button text
	dropDownBtn.initButtonText(btntxt, exAssets->getPrimaryFont(), btntxtcolor);

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
	dropDownButtonsKey.emplace_back(std::move(identifier));
	dropDownButtons.emplace(std::piecewise_construct, std::forward_as_tuple(dropDownButtonsKey[dropDownButtonsKey.size() - 1]), std::forward_as_tuple(btnColor, sf::Vector2f(), sf::Vector2f()));
	dropDownButtons[dropDownButtonsKey[dropDownButtonsKey.size() - 1]].initButtonText(dropDownButtonsKey[dropDownButtonsKey.size() - 1], usePrimaryFont ? exAssets->getPrimaryFont() : exAssets->getSecondaryFont(), txtColor);
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
	return dropDownButtons.at(identifier).isButtonClicked();
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
