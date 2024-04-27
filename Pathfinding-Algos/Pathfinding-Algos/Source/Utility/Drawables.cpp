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
// Class: Rounded Rect Convex Shape
// ================================================================================

Drawables::RoundedRect::RoundedRect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float cornerRounding, float rotation, Origin oPos)
	: ConvexShape(4)
{
	float topLeftOffset{ static_cast<float>(std::cos(7 / 8 * 2 * M_PI)) };

	setFillColor(color);

	//Vertex Points Of Rectangle
	rectVertex[0] = { (topLeftOffset * size.x / 2) + (size.x / 2), (topLeftOffset * size.y / 2) - (size.y / 2) };
	rectVertex[1] = { (topLeftOffset * size.x / 2) - (size.x / 2), (topLeftOffset * size.y / 2) - (size.y / 2) };
	rectVertex[2] = { (topLeftOffset * size.x / 2) - (size.x / 2), (topLeftOffset * size.y / 2) + (size.y / 2) };
	rectVertex[3] = { (topLeftOffset * size.x / 2) + (size.x / 2), (topLeftOffset * size.y / 2) + (size.y / 2) };

	sf::Vector2f roundingDirOffset { static_cast<float>(std::cos((1.0f / 8.0f) * (2 * M_PI))) , static_cast<float>(std::sin((1.0f / 8.0f) * (2 * M_PI))) };

	//If Rounding Is Present
	if (cornerRounding > 0.0f) {
		setPointCount((4 * Drawables::ADD_ROUNDING_POINTS));
		rectTotalPoints.reserve((4 * Drawables::ADD_ROUNDING_POINTS));

		for (int i{ 0 }; i < 4; i++, roundingDirOffset.x += std::cos(-M_PI / 2), roundingDirOffset.y -= std::cos(-M_PI / 2)) {
			sf::Vector2f offsetPos{ rectVertex[i].x + roundingDirOffset.x * cornerRounding,  rectVertex[i].y + roundingDirOffset.y * cornerRounding };
			sf::CircleShape test(10.0f, 30);
			test.setFillColor(sf::Color(255, 0, 0, 255));
			test.setPosition(offsetPos);
			exEvents->window.draw(test);

			std::cout << offsetPos.x  << " " << offsetPos.y << '\n';

			for (int j{ 0 }; j < Drawables::ADD_ROUNDING_POINTS; j++) {
				float angle = (2 * M_PI * ((Drawables::ADD_ROUNDING_POINTS * i) + j)) / (4 * Drawables::ADD_ROUNDING_POINTS);
				rectTotalPoints.push_back({ offsetPos.x + cornerRounding * std::cos(angle), offsetPos.y - cornerRounding * std::sin(angle) });
			}
		}
	}
	else {
		rectTotalPoints.reserve(4);

		for (int i{ 0 }; i < 4; i++) {
			rectTotalPoints.push_back(rectVertex[i]);
		}
	}

	//Set Convex Shape Points
	for (int i{ 0 }; i < rectTotalPoints.size(); i++) {
		setPoint(i, rectTotalPoints.at(i));
	}

	setPosition(pos);
	setRotation(rotation);

	Drawables::setOrigin(*this, getLocalBounds().getSize(), oPos);
}

// ================================================================================
// Transformable Origin Setter
// ================================================================================

void Drawables::setOrigin(sf::Transformable& drawables, sf::Vector2f const& size, Origin oPos) {

	//Switch Cases For Origin Setting
	switch (oPos) {
	case Origin::CENTER:
		drawables.setOrigin(size.x / 2, size.y / 2);
		break;
	case Origin::TOP_LEFT:
		drawables.setOrigin(0.0f, 0.0f);
		break;
	case Origin::TOP_RIGHT:
		drawables.setOrigin(size.x, 0.0f);
		break;
	case Origin::BOT_RIGHT:
		drawables.setOrigin(size.x, size.y);
		break;
	case Origin::BOT_LEFT:
		drawables.setOrigin(0.0f, size.y);
		break;
	default:
		break;
	}
}

// ================================================================================
// Rectangle Shape Initializer
// ================================================================================

void Drawables::initRectShape(sf::RectangleShape& drawables, sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	drawables.setSize(size);
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setFillColor(color);

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}

// ================================================================================
// Circle Shape Initializer
// ================================================================================

void Drawables::initCircleShape(sf::CircleShape& drawables, sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	drawables.setRadius(radius);
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setFillColor(color);

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}

// ================================================================================
// Sprite Initializer
// ================================================================================

void Drawables::initSprite(sf::Sprite& drawables, sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
{
	//Set Drawables Components
	drawables.setTexture(tex);
	drawables.setTextureRect(spritePos);
	drawables.setScale(size.x / (drawables.getLocalBounds().getSize().x), size.y / (drawables.getLocalBounds().getSize().y));
	drawables.setPosition(pos);
	drawables.setRotation(rotation);
	drawables.setColor({ 255, 255, 255, opacity });

	//Set Origin
	setOrigin(drawables, drawables.getLocalBounds().getSize(), oPos);
}

//#define POINTS 10
//sf::Shape& RoundedRectangle(float x, float y, float rectWidth, float rectHeight, float radius, const sf::Color& Col, float Outline, const sf::Color& OutlineCol)
//{
//	sf::ConvexShape* rrect = new sf::ConvexShape();
//	rrect->setOutlineThickness(Outline);
//	float X = 0, Y = 0;
//	for (int i = 0; i < POINTS; i++)
//	{
//		X += radius / POINTS;
//		Y = sqrt(radius * radius - X * X);
//		rrect->setPoint(X + x + rectWidth - radius, y - Y + radius, Col, OutlineCol);
//	}
//	Y = 0;
//	for (int i = 0; i < POINTS; i++)
//	{
//		Y += radius / POINTS;
//		X = sqrt(radius * radius - Y * Y);
//		rrect->(x + rectWidth + X - radius, y + rectHeight - radius + Y, Col, OutlineCol);
//	}
//	X = 0;
//	for (int i = 0; i < POINTS; i++)
//	{
//		X += radius / POINTS;
//		Y = sqrt(radius * radius - X * X);
//		rrect->AddPoint(x + radius - X, y + rectHeight - radius + Y, Col, OutlineCol);
//	}
//	Y = 0;
//	for (int i = 0; i < POINTS; i++)
//	{
//		Y += radius / POINTS;
//		X = sqrt(radius * radius - Y * Y);
//		rrect->AddPoint(x - X + radius, y + radius - Y, Col, OutlineCol);
//	}
//	return *rrect;
//
//}