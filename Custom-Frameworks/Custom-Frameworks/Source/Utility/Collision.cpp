/*****************************************************************************************************************
@file         Collision.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for all collision systems definition

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Collision.hpp"
#include "..\..\Header\Utility\Utils.hpp"

bool UI_Collision::Rect_Button(sf::FloatRect const& btnBound) {
	//Get Mouse Position
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(exEvents->window));

	//Check For Mouse Click Within Bounds
	if (mousePos.x >= (btnBound.left) && //Left Side
		mousePos.x <= (btnBound.left + btnBound.width) && //Right Side
		mousePos.y >= (btnBound.top) && //Top Side
		mousePos.y <= (btnBound.top + btnBound.height)) //Bottom Side
	{
		return true;
	}

	return false;
}