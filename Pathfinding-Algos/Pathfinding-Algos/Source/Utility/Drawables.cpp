/*****************************************************************************************************************
@file         Drawables.cpp
@project      Pathfinding Algorithms
@author       Zen Ho
@brief        This is the source file for drawables helper function defintions
Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Utility\Drawables.hpp"
#include "..\..\Header\Utility\Utils.hpp"

// ================================================================================
// Class: Template Base Drawable Class
// ================================================================================

// ================================================================================
// Class: Text Drawable
// ================================================================================

Drawables::D_Text::D_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize, float rotation, Origin oPos)
	: D_Base<sf::Text>()
{
	setFont(font);
	setString(txt);
	setCharacterSize(charSize);
	setFillColor(color);
	setPosition(pos);
	setRotation(rotation);

	//Set Origin Of Text
	Custom_SetOrigin(oPos);
}

// ================================================================================
// Class: Rounded Rect Convex Shape
// ================================================================================

Drawables::D_RoundedRectangle::D_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos)
	: D_Base<sf::ConvexShape>(), cornerRounding{rounding}
{
	//Center Point Of Rectangle
	sf::Vector2f centerPoint{ size.x / 2, size.y / 2 };

	//Vertex Points Of Rectangle
	rectVertex[0] = { centerPoint.x + (size.x / 2), centerPoint.y - (size.y / 2) };
	rectVertex[1] = { centerPoint.x - (size.x / 2), centerPoint.y - (size.y / 2) };
	rectVertex[2] = { centerPoint.x - (size.x / 2), centerPoint.y + (size.y / 2) };
	rectVertex[3] = { centerPoint.x + (size.x / 2), centerPoint.y + (size.y / 2) };

	//Clamp Cornder Rounding
	cornerRounding = std::clamp(rounding, 0.0f, (size.x < size.y ? size.x / 2 : size.y / 2));

	//Update Points Of Rectangle
	setPoints();
	update();

	//Set FillColor
	setFillColor(color);

	//Set Position & Rotation
	setPosition(pos);
	setRotation(rotation);

	//Set Origin Of Rect
	Custom_SetOrigin(oPos);
}

void Drawables::D_RoundedRectangle::setPoints() {

	//Container To Store Total Points In The Rect
	std::vector<sf::Vector2f> rectTotalPoints;
	
	//Check For Rounding
	if (cornerRounding > 0.0f) {
		//If Rounding Reserve Number Of Edges * Points Per Edge For Rounding
		setPointCount((RECT_EDGES * ROUNDING_POINTS_PER_EDGE));
		rectTotalPoints.reserve((RECT_EDGES * ROUNDING_POINTS_PER_EDGE));

		//Calculate Offset From Rect Edegs Angle & Length
		float offsetAngle{ (5.0f / 8.0f) * static_cast<float>(2 * M_PI) };
		float offsetHyp{ PythagoreomFunction(cornerRounding, cornerRounding, true) };

		//Initialize Every Point In Rounded Rect
		for (int i{ 0 }; i < RECT_EDGES; i++, offsetAngle += static_cast<float>(M_PI_2)) {

			//Caulate Offset Position Based On Rounding Size
			sf::Vector2f offsetPos{ rectVertex[i].x + (std::cos(offsetAngle) * offsetHyp),  rectVertex[i].y - (std::sin(offsetAngle) * offsetHyp) };

			for (int j{ 0 }; j < ROUNDING_POINTS_PER_EDGE; j++) {
				//Calculate Angle To Set Point From Offset Position
				float angle{ (static_cast<float>(2 * M_PI) * ((ROUNDING_POINTS_PER_EDGE * i) + j)) / (RECT_EDGES * ROUNDING_POINTS_PER_EDGE) };
				rectTotalPoints.push_back({ offsetPos.x + cornerRounding * std::cos(angle), offsetPos.y - cornerRounding * std::sin(angle) });
			}
		}
	}
	else {
		//If No Rounding ( 4 Points Reserved )
		setPointCount(RECT_EDGES);
		rectTotalPoints.reserve(RECT_EDGES);

		for (int i{ 0 }; i < RECT_EDGES; i++) {
			rectTotalPoints.push_back(rectVertex[i]);
		}
	}

	//Set Convex Shape Points
	for (int i{ 0 }; i < rectTotalPoints.size(); i++) {
		setPoint(i, rectTotalPoints.at(i));
	}
}

void Drawables::D_RoundedRectangle::setCornerRounding(float rounding) {

	//Clamp Cornder Rounding
	sf::Vector2f localSize = getLocalBounds().getSize();
	cornerRounding = std::clamp(rounding, 0.0f, (localSize.x < localSize.y ? localSize.x / 2 : localSize.y / 2));

	//Update New Points
	setPoints();
	update();
}

float Drawables::D_RoundedRectangle::getCornerRounding() const {
	return cornerRounding;
}

// ================================================================================
// Rectangle Shape Initializer
// ================================================================================

Drawables::D_Rectangle::D_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
	: D_Base<RectangleShape>()
{
	//Set Drawables Components
	setSize(size);
	setPosition(pos);
	setRotation(rotation);
	setFillColor(color);

	//Set Origin
	Custom_SetOrigin(oPos);
}

// ================================================================================
// Circle Shape Initializer
// ================================================================================

Drawables::D_Circle::D_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
	: D_Base<CircleShape>()
{
	//Set Drawables Components
	setRadius(radius);
	setPosition(pos);
	setRotation(rotation);
	setFillColor(color);

	//Set Origin
	Custom_SetOrigin(oPos);
}

// ================================================================================
// Sprite Initializer
// ================================================================================

Drawables::D_Sprite::D_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
	: D_Base<Sprite>()
{
	//Set Drawables Components
	setTexture(tex);
	setTextureRect(spritePos);
	setScale(size.x / (getLocalBounds().getSize().x), size.y / (getLocalBounds().getSize().y));
	Custom_SetFixedScale();
	setPosition(pos);
	setRotation(rotation);
	setColor({ 255, 255, 255, opacity });

	//Set Origin
	Custom_SetOrigin(oPos);
}
