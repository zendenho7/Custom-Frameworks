/*****************************************************************************************************************
@file         UserInterface.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file for the user interface classes & objects

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "..\..\Header\Utility\Utils.hpp"
#include "..\..\Header\Utility\Drawables.hpp"

namespace Interface {

	// ================================================================================
	// Rect Button Constants
	// ================================================================================
	const sf::Vector2f	BTN_HOVER_SCALE{ 1.05f, 1.05f };	//Percentage Of Button Size
	const float			BTN_HOVER_TIME{ 0.25f };		//Hover Time In Seconds
	const sf::Vector2f	BTN_TXT_TO_BTN_RATIO{ 0.75f, 0.5f };

	// ================================================================================
	// Class: Rect Button
	// ================================================================================
	class RectButton {
	private:
		//Drawable Rect
		Drawables::D_RoundedRectangle btnBase;

		//Drawable Text
		Drawables::D_Text btnTxt;

		//Hovering Operators
		bool b_HoverAnimationEnabled;
		bool b_Hovering;
		sf::Vector2f hoverScale;
		float hoverDuration;

		//Text To Button Ratio ( Text Will Fit Within This Ratio )
		sf::Vector2f textToBtnRatio;

		//Hover Operations
		void hoverButton();
		void normalButton();

		//Rescale Txt To Fit Text To Btn Ratio
		void rescaleTxt();
	public:

		//Default Constructor
		RectButton() : btnBase(), btnTxt(), b_HoverAnimationEnabled{ false }, b_Hovering{ false }, hoverDuration{ 0.0f }{}

		/// <summary>
		/// RectButton Constructor
		/// </summary>
		/// <param name="color">: Color Of Button</param>
		/// <param name="size">: Size Of Button</param>
		/// <param name="pos">: Position Of Button</param>
		/// <param name="rounding">: Rounding Of Button</param>
		/// <param name="rotation">: Rotation Of Button</param>
		/// <param name="oPos">: Origin Of Button</param>
		/// <param name="hover">: Hovering Enabled(true) or Disabled(false)</param>
		RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hoverAnimation = true);

		//Default Copy Constructor
		RectButton(RectButton const& copy) = default;

		//Default Copy Assignment
		RectButton& operator=(RectButton const& copy) = default;
		
		/// <summary>
		/// RectButton Setter
		/// </summary>
		/// <param name="color">: Color Of Button</param>
		/// <param name="size">: Size Of Button</param>
		/// <param name="pos">: Position Of Button</param>
		/// <param name="rounding">: Rounding Of Button</param>
		/// <param name="rotation">: Rotation Of Button</param>
		/// <param name="oPos">: Origin Of Button</param>
		/// <param name="hover">: Hovering Enabled(true) or Disabled(false)</param>
		void initRectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hoverAnimation = true);

		/// <summary>
		/// Hover Settings
		/// </summary>
		/// <param name="hover">: Hovering Enabled(true) or Disabled(false)</param>
		/// <param name="scale">: Target Scale Of Button When Hovering</param>
		/// <param name="duration">: Speed Of Hover Increase Till Target Hover Scale</param>
		void setHoverSettings(bool hover, sf::Vector2f const& scale, float duration);

		/// <summary>
		/// Init Button Text If Needed
		/// </summary>
		/// <param name="txt">: Text String</param>
		/// <param name="font">: Font Of Text</param>
		/// <param name="color">: Color Of Text</param>
		/// <param name="txtBtnRatio">: Ratio Of Button Allocated For Text</param>
		/// <param name="charSize">: Char Size Of D_Text (Load @ Default Size Of 72 For Higher Resolution ) | Size Can Be Changed By Scaling</param>
		/// <param name="oPos">: Origin Of Text</param>
		void initRectButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio = BTN_TXT_TO_BTN_RATIO, sf::Uint8 charSize = Drawables::DEF_CHAR_SIZE, Drawables::Origin oPos = Drawables::Origin::CENTER);

		//Set Text To Button Ratio ( Text Will Be Fit Within This Ratio )
		void setTextToButtonRatio(sf::Vector2f const& ratio);

		//Button Click Check
		bool isButtonClicked();

		//Get Hover Status
		bool getHoverStatus() const;

		//Set Button Text
		void setText(std::string const& txt);

		//Get Button Text
		std::string getText() const;

		//Set Button Position
		void setPosition(sf::Vector2f const& pos);

		//Get Button Position
		sf::Vector2f getPosition() const;

		//Set Button Size
		void setSize(sf::Vector2f const& size);

		//Get Button Size
		sf::Vector2f getSize() const;

		//Set Button Scale
		void setScale(sf::Vector2f const& scale);

		//Get Button Scale
		sf::Vector2f getScale() const;

		//Get Button Local Bounding
		sf::FloatRect getLocalBounds() const;

		//Get Button Global Bounding
		sf::FloatRect getGlobalBounds() const;

		//Set Btn Color
		void setButtonColor(sf::Color const& color);

		//Get Btn Color
		sf::Color getButtonColor() const;

		//Set Btn Txt Color
		void setTxtColor(sf::Color const& color);

		//Get Btn Txt Color
		sf::Color getTxtColor() const;

		//Set Btn Rounding
		void setButtonRounding(float rounding);

		//Get Button Rounding
		float getButtonRounding() const;

		//Draw Button Onto Render Target
		void Custom_Draw() const;

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
	};

	// ================================================================================
	// Class: DropDown
	// ================================================================================
	class Container {
	private:

	public:

	};

	// ================================================================================
	// Class: DropDown
	// ================================================================================
	enum class DropDownAlign : sf::Uint8 {
		DOWN_CENTER = 0,
		DOWN_LEFT,
		DOWN_RIGHT,
		UP_CENTER,
		UP_LEFT,
		UP_RIGHT,
	};

	enum class DropDownBtnType : sf::Uint8 {
		HOVER = 0,
		CLICK
	};

	enum class DropDownArrangement : sf::Uint8 {
		VERTICAL = 0,
		HORIZONTAL

	};

	class DropDown {
	private:

		//Button To Show DropDown
		RectButton triggerButton;

		//Drop Down Container
		Drawables::D_RoundedRectangle dropDownContainer;

		//Drop Down Booleans
		bool b_DropDownHidden;
		bool b_MouseOverDropDown;

		//Type & Style
		DropDownBtnType buttonType;
		DropDownAlign alignmentStyle;

		//Drop Down Components
		std::vector<std::string> dropDownButtonsKey;
		std::unordered_map<std::string, RectButton> dropDownButtons;

	public:
		//Default Constructor
		DropDown() : triggerButton(), dropDownContainer(), b_DropDownHidden{ true }, b_MouseOverDropDown{ false }, buttonType{ DropDownBtnType::HOVER }, alignmentStyle{ DropDownAlign::DOWN_CENTER } {}

		//DropDown Constructor
		DropDown(std::string const& triggerbtntxt, sf::Color const& triggerbtntxtcolor, sf::Color const& triggerbtncolor, sf::Vector2f const& triggerbtnsize, sf::Vector2f const& triggerbtnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding = 0, DropDownBtnType type = DropDownBtnType::HOVER, DropDownAlign alignment = DropDownAlign::DOWN_CENTER);

		//Default Copy Constructor
		DropDown(DropDown const& copy) = default;

		//Default Copy Assignment
		DropDown& operator=(DropDown const& copy) = default;

		//Set DropDown
		void initDropDown(std::string const& triggerbtntxt, sf::Color const& triggerbtntxtcolor, sf::Color const& triggerbtncolor, sf::Vector2f const& triggerbtnsize, sf::Vector2f const& triggerbtnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding = 0, DropDownBtnType type = DropDownBtnType::HOVER, DropDownAlign alignment = DropDownAlign::DOWN_CENTER);

		//Add Components To DropDown
		void addButtons(std::string const& identifier, sf::Color const& btnColor, sf::Color const& txtColor, bool usePrimaryFont = true);

		//Automatically Arrange Components Added
		void arrangeButtons(sf::Vector2f const& padding, float spaceBetweenButtons, float buttonRounding = 0.0f, DropDownArrangement arrangementStyle = DropDownArrangement::VERTICAL);

		//Check If Button Is Clicked
		bool isButtonClicked(std::string const& identifier);

		//Set Button Txt
		void setButtonText(std::string const& identifier, std::string const& txt);

		//Get Button Txt
		std::string getButtonText(std::string const& identifier) const;

		//Update DropDown
		void updateDropDown();

		//Draw DropDown
		void drawDropDown();

		//Data Serialization & Deserialization
		virtual std::string serialize() const;
		virtual void deserialize(std::string const& data);
		virtual std::istringstream& deserialize(std::istringstream& stream);
	};
}

#endif // !USERINTERFACE_HPP
