/*****************************************************************************************************************
@file         Collision.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the header file for all collision systems

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#pragma once

#ifndef COLLISION_HPP
#define COLLISION_HPP

namespace UI_Collision {
	
	//Collision Between Mouse & Rect Button
	bool Rect_Button(sf::FloatRect const& btnBound);
}

#endif //!COLLISION_HPP