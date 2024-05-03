/*****************************************************************************************************************
@file         Drawables.cpp
@project      Custom Framworks
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

void Drawables::D_Text::setD_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize, float rotation, Origin oPos)
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

void Drawables::D_Text::Custom_OffsetToCenter() {
	//Offset To Center Of Bounding Box
	move(0.0f, -(getGlobalBounds().getSize().y * 1.0f / 4.0f));
}

// ================================================================================
// Class: Rounded Rect Convex Shape
// ================================================================================

Drawables::D_RoundedRectangle::D_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos)
	: cornerRounding{ rounding }, D_Base<sf::ConvexShape>()
{
	//Construct Rounded Rect
	constructRoundedRect(color, size, pos, cornerRounding, rotation, oPos);
}

Drawables::D_RoundedRectangle::D_RoundedRectangle(D_RoundedRectangle const& copy)
	: cornerRounding{ copy.getCornerRounding() }, D_Base<sf::ConvexShape>()
{
	//Construct Rounded Rect
	constructRoundedRect(copy.getFillColor(), copy.getLocalBounds().getSize(), copy.getPosition(), cornerRounding, copy.getRotation(), copy.Custom_GetOrigin());
}

void Drawables::D_RoundedRectangle::setD_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos)
{
	//Init Corner Rounding
	cornerRounding = rounding;

	//Construct Rounded Rect
	constructRoundedRect(color, size, pos, cornerRounding, rotation, oPos);
}

void Drawables::D_RoundedRectangle::setD_RoundedRectangle(D_RoundedRectangle const& copy)
{
	//Init Corner Rounding
	cornerRounding = copy.getCornerRounding();

	//Construct Rounded Rect
	constructRoundedRect(copy.getFillColor(), copy.getLocalBounds().getSize(), copy.getPosition(), cornerRounding, copy.getRotation(), copy.Custom_GetOrigin());
}

void Drawables::D_RoundedRectangle::constructRoundedRect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos) {
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
		setPointCount(static_cast<size_t>(RECT_EDGES * ROUNDING_POINTS_PER_EDGE));
		rectTotalPoints.reserve(static_cast<size_t>(RECT_EDGES * ROUNDING_POINTS_PER_EDGE));

		//Calculate Offset From Rect Edegs Angle & Length
		float offsetAngle{ (5.0f / 8.0f) * static_cast<float>(2.0 * M_PI) };
		float offsetHyp{ PythagoreomFunction(cornerRounding, cornerRounding, true) };

		//Calculating Angle Of Curve Points
		float angleIncr { static_cast<float>((2.0 * M_PI) / (RECT_EDGES * (ROUNDING_POINTS_PER_EDGE - 2))) };
		float angle{ 0.0f };

		//Initialize Every Point In Rounded Rect
		for (int i{ 0 }; i < RECT_EDGES; i++, offsetAngle += static_cast<float>(M_PI_2)) {

			//Caulate Offset Position Based On Rounding Size
			sf::Vector2f offsetPos{ rectVertex[i].x + (std::cos(offsetAngle) * offsetHyp),  rectVertex[i].y - (std::sin(offsetAngle) * offsetHyp) };

			//Before Curve Points ( Safeguard The Shape Of Rectangle )
			rectTotalPoints.push_back({ offsetPos.x + (cornerRounding * std::cos(angle)), offsetPos.y - (cornerRounding * std::sin(angle)) });

			for (int j{ 0 }; j < (ROUNDING_POINTS_PER_EDGE - 2); j++) {
				//Calculate Angle To Set Point From Offset Position
				angle += angleIncr;
				rectTotalPoints.push_back({ offsetPos.x + (cornerRounding * std::cos(angle)), offsetPos.y - (cornerRounding * std::sin(angle)) });
			}

			//After Curve Points ( Safeguard The Shape Of Rectangle )
			rectTotalPoints.push_back({ offsetPos.x + (cornerRounding * std::cos(angle)), offsetPos.y - (cornerRounding * std::sin(angle)) });
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

sf::Vector2f  Drawables::D_RoundedRectangle::getSize() const {
	return getLocalBounds().getSize();
}

void  Drawables::D_RoundedRectangle::setSize(sf::Vector2f const& size) {
	//Center Point Of Rectangle
	sf::Vector2f centerPoint{ size.x / 2, size.y / 2 };

	//Vertex Points Of Rectangle
	rectVertex[0] = { centerPoint.x + (size.x / 2), centerPoint.y - (size.y / 2) };
	rectVertex[1] = { centerPoint.x - (size.x / 2), centerPoint.y - (size.y / 2) };
	rectVertex[2] = { centerPoint.x - (size.x / 2), centerPoint.y + (size.y / 2) };
	rectVertex[3] = { centerPoint.x + (size.x / 2), centerPoint.y + (size.y / 2) };

	//Update Points Of Rectangle
	setPoints();
	update();
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

void Drawables::D_Rectangle::setD_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
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

void Drawables::D_Circle::setD_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
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

void Drawables::D_Sprite::setD_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
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
