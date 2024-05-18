/*****************************************************************************************************************
@file         UserInterface.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file for the user interface classes & objects
Copyright (c) 2024 Zen Ho
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
	const sf::Vector2f	BTN_TXT_TO_BTN_RATIO{ 0.5f, 0.5f };

	// ================================================================================
	// Class: Rect Button
	// ================================================================================
	class RectButton {
	private:
		//Drawable Rect ( Base Of Button )
		Drawables::D_RoundedRectangle D_Rect;

		//Drawable Text
		Drawables::D_Text D_Text;

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
	public:

		//Default Constructor
		RectButton() = default;

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
		void initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio = BTN_TXT_TO_BTN_RATIO, sf::Uint8 charSize = Drawables::DEF_CHAR_SIZE, Drawables::Origin oPos = Drawables::Origin::CENTER);

		//Set Text To Button Ratio ( Text Will Be Fit Within This Ratio )
		void setTextToButtonRatio(sf::Vector2f const& ratio);

		//Button Click Check
		bool isButtonClicked();

		//Draw Button Onto Render Target
		void Custom_Draw() const;

		//Set Button Position
		void setPosition(sf::Vector2f const& pos);

		//Get Button Position
		sf::Vector2f getPosition() const;

		//Set Button Size
		void setScale(sf::Vector2f const& size);

		//Get Button Local Bounding
		sf::FloatRect getLocalBounds() const;

		//Get Button Global Bounding
		sf::FloatRect getGlobalBounds() const;

		//Get Hover Status
		bool getHoverStatus() const;
	};

	// ================================================================================
	// DropDown Enums
	// ================================================================================
	enum class DropDownAlign {
		DOWN_CENTER = 0,
		DOWN_LEFT,
		DOWN_RIGHT,
		UP_CENTER,
		UP_LEFT,
		UP_RIGHT,
	};

	enum class DropDownType {
		HOVER = 0,
		CLICK
	};

	// ================================================================================
	// Class: DropDown
	// ================================================================================
	class DropDown {
	private:

		//Drop Down Booleans
		bool b_DropDownHidden;
		bool b_MouseOverDropDown;

		//Type & Style
		DropDownType dropDownType;
		DropDownAlign alignmentStyle;
		bool b_ArrangeVertical;

		//Button To Show DropDown
		RectButton dropDownBtn;

		//Drop Down Container
		Drawables::D_RoundedRectangle dropDownContainer;

		//Drop Down Components
		std::vector<std::string> dropDownButtonsKey;
		std::unordered_map<std::string, RectButton> dropDownButtons;

	public:
		//Default Constructor
		DropDown() = default;

		//DropDown Constructor
		DropDown(sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding = 0, DropDownType type = DropDownType::HOVER, DropDownAlign alignment = DropDownAlign::DOWN_CENTER);

		//Add Components To DropDown
		void addButtons(std::string const& identifier, sf::Color const& btnColor, sf::Color const& txtColor, bool usePrimaryFont = true);

		//Automatically Arrange Components Added
		void arrangeButtons();

		//Update DropDown
		void Custom_Update();

		//Draw DropDown
		void Custom_Draw();
	};
}

#endif // !USERINTERFACE_HPP
