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

	//Rect Button Default Constants
	const sf::Vector2f	BTN_HOVER_SCALE{ 1.05f, 1.05f };	//Percentage Of Button Size
	const float			BTN_HOVER_TIME{ 0.25f };		//Hover Time In Seconds
	const sf::Vector2f	BTN_TXT_TO_BTN_RATIO{ 0.5f, 0.5f };

	//Button Interface
	class RectButton {
	private:
		//Drawable Rect ( Base Of Button )
		Drawables::D_RoundedRectangle D_Rect;

		//Drawable Text
		Drawables::D_Text D_Text;

		//Hovering Operators
		bool b_hoverEnabled;
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
		RectButton(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Drawables::Origin oPos = Drawables::Origin::CENTER, bool hover = true);

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
		sf::Vector2f const& getPosition() const;

		//Set Button Size
		void setScale(sf::Vector2f const& size);

		//Get Button Local Bounding
		sf::FloatRect const& getLocalBounds() const;

		//Get Button Global Bounding
		sf::FloatRect const& getGlobalBounds() const;
	};

	//Drop Down Alignment
	enum class DropDownAlign {
		CENTER = 0,
		LEFT,
		RIGHT
	};

	//Drop Down Interface
	class DropDown {
	private:

		//Drop Down Booleans
		bool b_DropDownHidden;

		//Arrangement Style
		bool b_ArrangeVertical;

		//Button To Show DropDown
		RectButton dropDownBtn;

		//Drop Down Container
		Drawables::D_RoundedRectangle dropDownContainer;

		//Drop Down Components
		std::map<std::string, RectButton> dropDownButtons;

	public:
		//Default Constructor
		DropDown() = default;

		//DropDown Constructor
		DropDown(sf::Color const& btncolor, sf::Vector2f const& btnsize, sf::Vector2f const& btnpos, sf::Color const& dropdowncolor, sf::Vector2f const& dropdownsize, float rounding = 0, DropDownAlign alignment = DropDownAlign::CENTER)
			: dropDownBtn(btncolor, btnsize, btnpos, rounding), dropDownContainer(dropdowncolor, dropdownsize, sf::Vector2f(0.0f, 0.0f), rounding), b_DropDownHidden{true}, b_ArrangeVertical{false}
		{
			switch (alignment) {
			case DropDownAlign::CENTER:
				dropDownContainer.setPosition(dropDownBtn.getPosition().x, dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
				break;
			case DropDownAlign::LEFT:
				dropDownContainer.setPosition(dropDownBtn.getPosition().x + (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
				break;
			case DropDownAlign::RIGHT:
				dropDownContainer.setPosition(dropDownBtn.getPosition().x - (std::abs(dropDownContainer.getGlobalBounds().width - dropDownBtn.getGlobalBounds().width) / 4), dropDownBtn.getPosition().y + (dropDownBtn.getGlobalBounds().height / 2) + (dropDownContainer.getGlobalBounds().height / 2));
				break;
			default:
				break;
			}
		}

		//Add Components To DropDown ( Position & Sized Will Be Altered To Fit DropDown )
		void addComponents(std::string const& identifier) {
			//dropDownComponents.emplace(identifier, obj);
		} 

		//Automatically Arrange Components Added
		void arrangeComponents() {

		}

		//Update DropDown
		void Custom_Update() {
			if (dropDownBtn.isButtonClicked()) {
				b_DropDownHidden = !b_DropDownHidden;
			}
		}

		//Draw DropDown
		void Custom_Draw() {
			//Draw DropDown Container
			dropDownBtn.Custom_Draw();

			if (!b_DropDownHidden) {
				exEvents->window.draw(dropDownContainer);
			}
		}
	};
}

#endif // !USERINTERFACE_HPP
