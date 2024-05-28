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

void Interface::RectButton::initRectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Drawables::Origin oPos, bool hoverAnimation)
{
	btnBase.initD_RoundedRectangle(color, size, pos, rounding, rotation, oPos);
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

void Interface::RectButton::initRectButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio, sf::Uint8 charSize, Drawables::Origin oPos) {
	
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

void Interface::RectButton::setText(std::string const& txt) {
	btnTxt.Custom_SetString(txt);
	rescaleTxt();
}

std::string Interface::RectButton::getText() const {
	return btnTxt.getString();
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
// Class: Panel
// ================================================================================

Interface::Panel::Panel(sf::Color const& panelColor, sf::Vector2f const& panelSize, sf::Vector2f const& panelPos, float panelRounding)
	: container(panelColor, panelSize, panelPos, panelRounding), componentsArea()
{
}

void Interface::Panel::initPanel(sf::Color const& panelColor, sf::Vector2f const& panelSize, sf::Vector2f const& panelPos, float panelRounding) {
	container.initD_RoundedRectangle(panelColor, panelSize, panelPos, panelRounding);
}

sf::Vector2f Interface::Panel::calculateComponentsScale(sf::Vector2f const& targetSize, sf::Vector2f const& currSize) {

	sf::Vector2f txtratio{ currSize.x / targetSize.x, currSize.y / targetSize.y };
	float maxScale{ std::min(targetSize.x / currSize.x, targetSize.y / currSize.y) };
	float scale{ txtratio.x > txtratio.y
		? std::clamp(targetSize.x, 0.0f, maxScale)
		: std::clamp(targetSize.y, 0.0f, maxScale) };

	return sf::Vector2f(scale, scale);
}

void Interface::Panel::addSpriteComponent(std::string const& identifier, float sizeRatio, sf::Texture const& tex, sf::IntRect const& spritePos, sf::Uint8 opacity) {
	panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, PanelComponentTypes::SPRITE));
	panelSprites.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Sprite, float>(Drawables::D_Sprite(tex, spritePos, sf::Vector2f(), sf::Vector2f(),0.0f, opacity), sizeRatio)));
}

void Interface::Panel::addTextComponent(std::string const& identifier, float sizeRatio, std::string const& txt, sf::Font const& font, sf::Color const& txtColor) {
	panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, PanelComponentTypes::TEXT));
	panelTexts.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Text, float>(Drawables::D_Text(txt, font, txtColor, sf::Vector2f()), sizeRatio)));
}

void Interface::Panel::addButtonComponent(std::string const& identifier, float sizeRatio, sf::Color const& btnColor, float buttonRounding, std::string const& btntxt, sf::Font const& font, sf::Color const& txtColor) {
	panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, PanelComponentTypes::BUTTON));
	panelButtons.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<RectButton, float>(RectButton(btnColor, sf::Vector2f(buttonRounding * 2, buttonRounding * 2), sf::Vector2f(), buttonRounding), sizeRatio)));
	panelButtons.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.initRectButtonText(btntxt, font, txtColor);
}

void Interface::Panel::addSeperatorComponent(std::string const& identifier, float sizeRatio) {
	panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, PanelComponentTypes::SEPERATOR));
	panelSeparator.emplace(panelComponentsKey.at(panelComponentsKey.size() - 1).first, sizeRatio);
}

void Interface::Panel::arrangeComponents(sf::Vector2f const& padding, float spacebetweenComponents, PanelArrangment arrangementStyle) {
	//Area Left To Occupy After Accounting For Padding
	componentsArea = { container.getGlobalBounds().getSize() - padding - padding };
	float totalSpace{ spacebetweenComponents * (panelComponentsKey.size() - 1) };

	sf::Vector2f startpos;

	switch (arrangementStyle) {
	case PanelArrangment::VERTICAL:
		startpos = { container.Custom_GetOriginPosition().x, container.Custom_GetOriginPosition().y - (componentsArea.y / 2) };
		componentsArea.y -= totalSpace;

		for (std::pair<std::string, PanelComponentTypes> const& key : panelComponentsKey) {
			switch (key.second) {
			case PanelComponentTypes::SPRITE:
				panelSprites.at(key.first).first.setScale(calculateComponentsScale({ componentsArea.x, panelSprites.at(key.first).second * componentsArea.y }, panelSprites.at(key.first).first.getLocalBounds().getSize()));
				panelSprites.at(key.first).first.setPosition(startpos + sf::Vector2f(0.0f, (panelSprites.at(key.first).second * componentsArea.y) / 2));
				panelSprites.at(key.first).first.Custom_SetFixedScale();
				(startpos.y += (panelSprites.at(key.first).second * componentsArea.y)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::TEXT:
				panelTexts.at(key.first).first.setScale(calculateComponentsScale({ componentsArea.x, panelTexts.at(key.first).second * componentsArea.y }, panelTexts.at(key.first).first.getLocalBounds().getSize()));
				panelTexts.at(key.first).first.setPosition(startpos + sf::Vector2f(0.0f, (panelTexts.at(key.first).second * componentsArea.y) / 2));
				panelTexts.at(key.first).first.Custom_SetFixedScale();
				panelTexts.at(key.first).first.Custom_OffsetToCenter();
				(startpos.y += (panelTexts.at(key.first).second * componentsArea.y)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::BUTTON:
				panelButtons.at(key.first).first.setSize({ componentsArea.x, panelButtons.at(key.first).second * componentsArea.y });
				panelButtons.at(key.first).first.setPosition(startpos + sf::Vector2f(0.0f, (panelButtons.at(key.first).second * componentsArea.y) / 2));
				panelButtons.at(key.first).first.setButtonRounding(panelButtons.at(key.first).first.getButtonRounding());
				(startpos.y += (panelButtons.at(key.first).second * componentsArea.y)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::SEPERATOR:
				(startpos.y += (panelSeparator.at(key.first) * componentsArea.y)) += spacebetweenComponents;
				break;
			default:
				break;
			}
		}
		break;
	case PanelArrangment::HORIZONTAL:
		startpos = { container.Custom_GetOriginPosition().x - (componentsArea.x / 2), container.Custom_GetOriginPosition().y };
		componentsArea.x -= totalSpace;

		for (std::pair<std::string, PanelComponentTypes> const& key : panelComponentsKey) {
			switch (key.second) {
			case PanelComponentTypes::SPRITE:
				panelSprites.at(key.first).first.setScale(calculateComponentsScale({ panelSprites.at(key.first).second * componentsArea.x, componentsArea.y }, panelSprites.at(key.first).first.getLocalBounds().getSize()));
				panelSprites.at(key.first).first.setPosition(startpos + sf::Vector2f((panelSprites.at(key.first).second * componentsArea.x) / 2, 0.0f));
				panelSprites.at(key.first).first.Custom_SetFixedScale();
				(startpos.x += (panelSprites.at(key.first).second * componentsArea.x)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::TEXT:
				panelTexts.at(key.first).first.setScale(calculateComponentsScale({ panelTexts.at(key.first).second * componentsArea.x, componentsArea.y }, panelTexts.at(key.first).first.getLocalBounds().getSize()));
				panelTexts.at(key.first).first.setPosition(startpos + sf::Vector2f((panelTexts.at(key.first).second * componentsArea.x) / 2, 0.0f));
				panelTexts.at(key.first).first.Custom_SetFixedScale();
				panelTexts.at(key.first).first.Custom_OffsetToCenter();
				(startpos.x += (panelTexts.at(key.first).second * componentsArea.x)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::BUTTON:
				panelButtons.at(key.first).first.setSize({ panelButtons.at(key.first).second * componentsArea.x, componentsArea.y });
				panelButtons.at(key.first).first.setPosition(startpos + sf::Vector2f((panelButtons.at(key.first).second * componentsArea.x) / 2, 0.0f));
				panelButtons.at(key.first).first.setButtonRounding(panelButtons.at(key.first).first.getButtonRounding());
				(startpos.x += (panelButtons.at(key.first).second * componentsArea.x)) += spacebetweenComponents;
				break;
			case PanelComponentTypes::SEPERATOR:
				(startpos.x += (panelSeparator.at(key.first) * componentsArea.x)) += spacebetweenComponents;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

bool Interface::Panel::isButtonClicked(std::string const& identifier) {
	return panelButtons.at(identifier).first.isButtonClicked();
}

void Interface::Panel::setButtonText(std::string const& identifier, std::string const& txt) {
	panelButtons.at(identifier).first.setText(txt);
}

std::string Interface::Panel::getButtonText(std::string const& identifier) const {
	return panelButtons.at(identifier).first.getText();
}

void Interface::Panel::setButtonColor(std::string const& identifier, sf::Color const& color) {
	panelButtons.at(identifier).first.setButtonColor(color);
}

sf::Color Interface::Panel::getButtonColor(std::string const& identifier) const {
	return panelButtons.at(identifier).first.getButtonColor();
}

void Interface::Panel::setTextString(std::string const& identifier, std::string const& txt) {
	panelTexts.at(identifier).first.Custom_SetString(txt);
}

std::string Interface::Panel::getTextString(std::string const& identifier) const {
	return panelTexts.at(identifier).first.getString();
}

void Interface::Panel::setTextColor(std::string const& identifier, sf::Color const& color) {
	panelTexts.at(identifier).first.setFillColor(color);
}

sf::Color Interface::Panel::getTextColor(std::string const& identifier) const {
	return panelTexts.at(identifier).first.getFillColor();
}

void Interface::Panel::drawPanel() {

	//Draw Container
	exEvents->window.draw(container);

	//Draw All Components
	for (std::pair<std::string, PanelComponentTypes> const& key : panelComponentsKey) {
		switch (key.second) {
		case PanelComponentTypes::SPRITE:
			panelSprites.at(key.first).first.Custom_Draw();
			break;
		case PanelComponentTypes::TEXT:
			panelTexts.at(key.first).first.Custom_Draw();
			break;
		case PanelComponentTypes::BUTTON:
			panelButtons.at(key.first).first.Custom_Draw();
			break;
		case PanelComponentTypes::SEPERATOR:
			break;
		default:
			break;
		}
	}
}

std::string Interface::Panel::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << container.serialize() << " " << componentsArea.x  << " " << componentsArea.y << " " << panelComponentsKey.size() << " ";

	//Serialize All Components
	for (std::pair<std::string, PanelComponentTypes> const& key : panelComponentsKey) {
		oss << key.first.size() << " " << key.first << " " << static_cast<int>(key.second) << " ";

		switch (key.second) {
		case PanelComponentTypes::SPRITE:
			oss << panelSprites.at(key.first).first.serialize() << " " << panelSprites.at(key.first).second << " ";
			break;
		case PanelComponentTypes::TEXT:
			oss << panelTexts.at(key.first).first.serialize() << " " << panelTexts.at(key.first).second << " ";
			break;
		case PanelComponentTypes::BUTTON:
			oss << panelButtons.at(key.first).first.serialize() << " " << panelButtons.at(key.first).second << " ";
			break;
		case PanelComponentTypes::SEPERATOR:
			oss << panelSeparator.at(key.first) << " ";
			break;
		default:
			break;
		}
	}

	return oss.str();
}

void Interface::Panel::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	int Paneltype;
	size_t size;

	//Output Stream From String
	container.deserialize(iss) >> componentsArea.x >> componentsArea.y >> size;

	//Clear Containers
	panelComponentsKey.clear();
	panelSprites.clear();
	panelTexts.clear();
	panelButtons.clear();
	panelSeparator.clear();

	for (size_t i{ 0 }; i < size; i++) {

		//Extracting String Identifier
		size_t sizeofstr;
		std::string identifier;

		iss >> sizeofstr;
		iss.seekg(1, std::ios::cur);

		for (size_t j{ 0 }; j < sizeofstr; j++) {
			char strchar;
			iss.get(strchar);
			identifier += strchar;
		}

		iss >> Paneltype;
		panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, static_cast<PanelComponentTypes>(Paneltype)));
		
		switch (panelComponentsKey[panelComponentsKey.size() - 1].second) {
		case PanelComponentTypes::SPRITE:
			panelSprites.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Sprite, float>()));
			panelSprites.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(iss) >> panelSprites.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::TEXT:
			panelTexts.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Text, float>()));
			panelTexts.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(iss) >> panelTexts.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::BUTTON:
			panelButtons.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<RectButton, float>()));
			panelButtons.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(iss) >> panelButtons.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::SEPERATOR:
			panelSeparator.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple());
			iss >> panelSeparator.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first);
			break;
		default:
			break;
		}
	}
}

std::istringstream& Interface::Panel::deserialize(std::istringstream& stream) {
	//Temporary Variables
	int Paneltype;
	size_t size;

	//Output Stream From String
	container.deserialize(stream) >> componentsArea.x >> componentsArea.y >> size;

	//Clear Containers
	panelComponentsKey.clear();
	panelSprites.clear();
	panelTexts.clear();
	panelButtons.clear();
	panelSeparator.clear();

	for (size_t i{ 0 }; i < size; i++) {

		//Extracting String Identifier
		size_t sizeofstr;
		std::string identifier;

		stream >> sizeofstr;
		stream.seekg(1, std::ios::cur);
		for (size_t j{ 0 }; j < sizeofstr; j++) {
			char strchar;
			stream.get(strchar);
			identifier += strchar;
		}

		stream >> Paneltype;
		panelComponentsKey.emplace_back(std::pair<std::string, PanelComponentTypes>(identifier, static_cast<PanelComponentTypes>(Paneltype)));

		switch (panelComponentsKey[panelComponentsKey.size() - 1].second) {
		case PanelComponentTypes::SPRITE:
			panelSprites.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Sprite, float>()));
			panelSprites.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(stream) >> panelSprites.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::TEXT:
			panelTexts.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<Drawables::D_Text, float>()));
			panelTexts.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(stream) >> panelTexts.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::BUTTON:
			panelButtons.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple(std::pair<RectButton, float>()));
			panelButtons.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).first.deserialize(stream) >> panelButtons.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first).second;
			break;
		case PanelComponentTypes::SEPERATOR:
			panelSeparator.emplace(std::piecewise_construct, std::forward_as_tuple(panelComponentsKey.at(panelComponentsKey.size() - 1).first), std::forward_as_tuple());
			stream >> panelSeparator.at(panelComponentsKey.at(panelComponentsKey.size() - 1).first);
			break;
		default:
			break;
		}
	}

	return stream;
}

// ================================================================================
// Class: DropDown
// ================================================================================

Interface::DropDown::DropDown(std::string const& triggerbtntxt, sf::Color const& triggerbtntxtcolor, sf::Color const& triggerbtncolor, sf::Vector2f const& triggerbtnsize, sf::Vector2f const& triggerbtnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownBtnType type, DropDownAlign alignment)
	: triggerButton(triggerbtncolor, triggerbtnsize, triggerbtnpos, rounding, 0.0f, Drawables::Origin::CENTER, false), dropDownContainer(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding),
	b_DropDownHidden{ true }, b_MouseOverDropDown{ false }, alignmentStyle{ alignment }, buttonType{ type }
{
	//Init DropDown Button text
	triggerButton.initRectButtonText(triggerbtntxt, exAssets->getPrimaryFont(), triggerbtntxtcolor);

	//Set Position Of DropDown Container
	switch (alignmentStyle) {
	case DropDownAlign::DOWN_CENTER:
		dropDownContainer.setPosition(triggerButton.getPosition().x, triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_LEFT:
		dropDownContainer.setPosition(triggerButton.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_RIGHT:
		dropDownContainer.setPosition(triggerButton.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_CENTER:
		dropDownContainer.setPosition(triggerButton.getPosition().x, triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_LEFT:
		dropDownContainer.setPosition(triggerButton.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_RIGHT:
		dropDownContainer.setPosition(triggerButton.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	default:
		break;
	}
}

void Interface::DropDown::initDropDown(std::string const& triggerbtntxt, sf::Color const& triggerbtntxtcolor, sf::Color const& triggerbtncolor, sf::Vector2f const& triggerbtnsize, sf::Vector2f const& triggerbtnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding, DropDownBtnType type, DropDownAlign alignment)
{
	alignmentStyle = alignment;
	buttonType = type;
	triggerButton.initRectButton(triggerbtncolor, triggerbtnsize, triggerbtnpos, rounding, 0.0f, Drawables::Origin::CENTER, false);
	dropDownContainer.initD_RoundedRectangle(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding);
	//Init DropDown Button text
	triggerButton.initRectButtonText(triggerbtntxt, exAssets->getPrimaryFont(), triggerbtntxtcolor);

	//Set Position Of DropDown Container
	switch (alignmentStyle) {
	case DropDownAlign::DOWN_CENTER:
		dropDownContainer.setPosition(triggerButton.getPosition().x, triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_LEFT:
		dropDownContainer.setPosition(triggerButton.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::DOWN_RIGHT:
		dropDownContainer.setPosition(triggerButton.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y + (triggerButton.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_CENTER:
		dropDownContainer.setPosition(triggerButton.getPosition().x, triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_LEFT:
		dropDownContainer.setPosition(triggerButton.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	case DropDownAlign::UP_RIGHT:
		dropDownContainer.setPosition(triggerButton.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - triggerButton.getGlobalBounds().width) / 2), triggerButton.getPosition().y - (triggerButton.getGlobalBounds().height / 2) - (dropDownContainer.getGlobalBounds().height / 2));
		break;
	default:
		break;
	}
}

void Interface::DropDown::addButtons(std::string const& identifier, sf::Color const& btnColor, sf::Color const& txtColor, bool usePrimaryFont) {
	dropDownButtonsKey.emplace_back(identifier);
	dropDownButtons.emplace(std::piecewise_construct, std::forward_as_tuple(dropDownButtonsKey[dropDownButtonsKey.size() - 1]), std::forward_as_tuple(btnColor, sf::Vector2f(), sf::Vector2f()));
	dropDownButtons[dropDownButtonsKey[dropDownButtonsKey.size() - 1]].initRectButtonText(dropDownButtonsKey[dropDownButtonsKey.size() - 1], usePrimaryFont ? exAssets->getPrimaryFont() : exAssets->getSecondaryFont(), txtColor);
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
			dropDownButtons.at(key).setSize(btnSize);
			dropDownButtons.at(key).setPosition(startpos);
			dropDownButtons.at(key).setButtonRounding(buttonRounding);
			(startpos.y += btnSize.y) += spaceBetweenButtons;
		}
		break;
	case DropDownArrangement::HORIZONTAL:
		btnSize = { (workableArea.x - totalSpace) / dropDownButtonsKey.size(), workableArea.y };
		startpos = { dropDownContainer.Custom_GetOriginPosition().x - (workableArea.x / 2) + (btnSize.x / 2), dropDownContainer.Custom_GetOriginPosition().y };
		for (std::string const& key : dropDownButtonsKey) {
			dropDownButtons.at(key).setSize(btnSize);
			dropDownButtons.at(key).setPosition(startpos);
			dropDownButtons.at(key).setButtonRounding(buttonRounding);
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

void Interface::DropDown::setButtonText(std::string const& identifier, std::string const& txt) {
	dropDownButtons.at(identifier).setText(txt);
}

std::string Interface::DropDown::getButtonText(std::string const& identifier) const {
	return dropDownButtons.at(identifier).getText();
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
		triggerButton.isButtonClicked();

		//Show Or Hide DropDown
		if (triggerButton.getHoverStatus()) {
			b_DropDownHidden = false;
		}
		else {
			if (!b_MouseOverDropDown) {
				b_DropDownHidden = true;
			}
		}
		break;
	case DropDownBtnType::CLICK:
		if (triggerButton.isButtonClicked()) {
			b_DropDownHidden = !b_DropDownHidden;
		}
		break;
	default:
		break;
	}
}

void Interface::DropDown::drawDropDown() {
	//Draw DropDown Btn Activator
	triggerButton.Custom_Draw();

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
	oss << triggerButton.serialize() << " " << dropDownContainer.serialize() << " "
		<< b_DropDownHidden << " " << b_MouseOverDropDown << " "
		<< static_cast<int>(buttonType) << " " << static_cast<int>(alignmentStyle) << " "
		<< dropDownButtonsKey.size() << " ";

	for (std::string const& key : dropDownButtonsKey) {
		oss << key.size() << " " << key << " " << dropDownButtons.at(key).serialize() << " ";
	}

	return oss.str();
}

void Interface::DropDown::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	int btntype;
	int alignstyle;
	size_t size;

	//Output Stream From String
	triggerButton.deserialize(iss);
	dropDownContainer.deserialize(iss)
		>> b_DropDownHidden >> b_MouseOverDropDown
		>> btntype >> alignstyle >> size;

	buttonType = static_cast<DropDownBtnType>(btntype);
	alignmentStyle = static_cast<DropDownAlign>(alignstyle);

	dropDownButtonsKey.clear();
	dropDownButtons.clear();

	for (size_t i{ 0 }; i < size; i++) {
		//Extracting String Identifier
		size_t sizeofstr;
		std::string identifier;
		iss >> sizeofstr;

		iss.seekg(1, std::ios::cur);

		for (size_t j{ 0 }; j < sizeofstr; j++) {
			char charstr;
			iss.get(charstr);
			identifier += charstr;
		}

		dropDownButtonsKey.emplace_back(identifier);
		dropDownButtons.emplace(std::piecewise_construct, std::forward_as_tuple(dropDownButtonsKey.at(dropDownButtonsKey.size() - 1)), std::forward_as_tuple());
		dropDownButtons.at(dropDownButtonsKey.at(dropDownButtonsKey.size() - 1)).deserialize(iss);
	}
}

std::istringstream& Interface::DropDown::deserialize(std::istringstream& stream) {
	//Temporary Variables
	int btntype;
	int alignstyle;
	size_t size;

	//Output Stream From String
	triggerButton.deserialize(stream);
	dropDownContainer.deserialize(stream)
		>> b_DropDownHidden >> b_MouseOverDropDown
		>> btntype >> alignstyle >> size;

	buttonType = static_cast<DropDownBtnType>(btntype);
	alignmentStyle = static_cast<DropDownAlign>(alignstyle);

	dropDownButtonsKey.clear();
	dropDownButtons.clear();

	for (size_t i{ 0 }; i < size; i++) {
		//Extracting String Identifier
		size_t sizeofstr;
		std::string identifier;
		stream >> sizeofstr;

		for (size_t j{ 0 }; j < sizeofstr; j++) {

			stream.seekg(1, std::ios::cur);

			char charstr;
			stream.get(charstr);
			identifier += charstr;
		}

		dropDownButtonsKey.emplace_back(identifier);
		dropDownButtons.emplace(std::piecewise_construct, std::forward_as_tuple(dropDownButtonsKey.at(dropDownButtonsKey.size() - 1)), std::forward_as_tuple());
		dropDownButtons.at(dropDownButtonsKey.at(dropDownButtonsKey.size() - 1)).deserialize(stream);
	}

	return stream;
}
