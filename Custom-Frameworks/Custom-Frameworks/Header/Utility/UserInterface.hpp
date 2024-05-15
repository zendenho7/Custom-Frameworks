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

	//Interface Default Constants
	const sf::Vector2f	HOVER_SCALE{ 1.05f, 1.05f };	//Percentage Of Button Size
	const float			HOVER_TIME{ 0.25f };		//Hover Time In Seconds
	const sf::Vector2f	DEF_TXT_TO_BTN_RATIO{ 0.5f, 0.5f };

	//Button Interface
	class RectButton {
	private:
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

		//Drawable Rect ( Base Of Button )
		Drawables::D_RoundedRectangle D_Rect;

		//Drawable Text
		Drawables::D_Text D_Text;

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
		void initButtonText(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& txtBtnRatio = DEF_TXT_TO_BTN_RATIO, sf::Uint8 charSize = Drawables::DEF_CHAR_SIZE, Drawables::Origin oPos = Drawables::Origin::CENTER);

		//Set Text To Button Ratio ( Text Will Be Fit Within This Ratio )
		void setTextToButtonRatio(sf::Vector2f const& ratio);

		//Button Click Check
		bool isButtonClicked();

		//Draw Button Onto Render Target
		void Custom_Draw() const;
	};

	template <typename T>
	class DropDown {
	private:
		//Drop Down Type
		using dropDownType = T;

		//Drop Down Booleans
		bool b_DropDownHidden;

		//Drop Down Container
		Drawables::D_RoundedRectangle dropDownContainer;

		//Drop Down Components
		std::vector<dropDownType> dropDownComponents;

	public:
		//Default Constructor
		DropDown() = default;

		//DropDown Constructor
		DropDown(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, bool startHidden = true)
			: dropDownContainer(color, size, pos, rounding), b_DropDownHidden{ startHidden } {}

		//Add Components To DropDown
		void addComponents(dropDownType && obj) {
			dropDownComponents.emplace_back(std::move(obj));
		} 

		//Draw DropDown
		void Custom_Draw() const {
			//Draw DropDown Container
			exEvents->window.draw(dropDownContainer);

			//Draw All Components
			for (dropDownType const& elem : dropDownComponents) {
				elem.Custom_Draw();
			}
		}
	};
}

#endif // !USERINTERFACE_HPP
