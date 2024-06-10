/*****************************************************************************************************************
@file         Collision.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file for all collision systems

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef COLLISION_HPP
#define COLLISION_HPP

namespace UI_Collision {
	
	//Collision Between Mouse & Rect Button
	bool Rect_Button(sf::FloatRect const& btnBound);
}

#endif //!COLLISION_HPP