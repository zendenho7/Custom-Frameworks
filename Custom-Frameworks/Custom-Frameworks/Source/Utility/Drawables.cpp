/*****************************************************************************************************************
@file         Drawables.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This is the source file for drawables helper function defintions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
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

void Drawables::D_Text::initD_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize, float rotation, Origin oPos)
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

void Drawables::D_Text::Custom_SetString(std::string const& txt) {
	setString(txt);

	//Set Origin Based On Text Size
	Custom_UpdateOrigin();
}

void Drawables::D_Text::Custom_SetGlobalSize(sf::Vector2f const& size) {
	setScale(size.x / getLocalBounds().getSize().x, size.y / getLocalBounds().getSize().y);
}

void Drawables::D_Text::Custom_Draw() const {
	exEvents->window.draw(*this);
}

std::string Drawables::D_Text::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_Base<sf::Text>::serialize() << " " << static_cast<std::string>(getString()) << " " << getCharacterSize() << " "
		<< getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << " " << getFillColor().a << " "
		<< getPosition().x << " " << getPosition().y << " " << getRotation() << " " << static_cast<int>(Custom_GetOrigin()) << " "
		<< getLetterSpacing() << " " << getLineSpacing() << " " << getOutlineThickness() << " "
		<< getOutlineColor().r << " " << getOutlineColor().g << " " << getOutlineColor().b << " " << getOutlineColor().a << " "
		<< getScale().x << " " << getScale().y << " " << getStyle();

	return oss.str();
}

void Drawables::D_Text::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	;
	std::string str;
	unsigned int charSize;
	sf::Color color;
	sf::Vector2f pos;
	float rotation;
	int oPos;
	float letterspacing;
	float linespacing;
	float outlinethickness;
	sf::Color outlinecolor;
	sf::Vector2f scale;
	sf::Uint32 style;

	//Input Stream From String
	D_Base<sf::Text>::deserialize(iss) >> str >> charSize >> color.r >> color.g >> color.b >> color.a
		>> pos.x >> pos.y >> rotation >> oPos >> letterspacing >> linespacing >> outlinethickness
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a >> scale.x >> scale.y
		>> style;

	setFont(getFont() ? *getFont() : exAssets->getPrimaryFont());
	setString(str);
	setCharacterSize(charSize);
	setFillColor(color);
	setPosition(pos);
	setRotation(rotation);
	setLetterSpacing(letterspacing);
	setLineSpacing(linespacing);
	setOutlineThickness(outlinethickness);
	setOutlineColor(outlinecolor);
	setScale(scale);
	setStyle(style);

	//Set Origin Of Text
	Custom_SetOrigin(static_cast<Origin>(oPos));
}

std::istringstream& Drawables::D_Text::deserialize(std::istringstream& stream) {
	//Temporary Variables
	;
	std::string str;
	unsigned int charSize;
	sf::Color color;
	sf::Vector2f pos;
	float rotation;
	int oPos;
	float letterspacing;
	float linespacing;
	float outlinethickness;
	sf::Color outlinecolor;
	sf::Vector2f scale;
	sf::Uint32 style;

	//Input Stream From String
	D_Base<sf::Text>::deserialize(stream) >> str >> charSize >> color.r >> color.g >> color.b >> color.a
		>> pos.x >> pos.y >> rotation >> oPos >> letterspacing >> linespacing >> outlinethickness
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a >> scale.x >> scale.y
		>> style;

	setFont(getFont() ? *getFont() : exAssets->getPrimaryFont());
	setString(str);
	setCharacterSize(charSize);
	setFillColor(color);
	setPosition(pos);
	setRotation(rotation);
	setLetterSpacing(letterspacing);
	setLineSpacing(linespacing);
	setOutlineThickness(outlinethickness);
	setOutlineColor(outlinecolor);
	setScale(scale);
	setStyle(style);

	//Set Origin Of Text
	Custom_SetOrigin(static_cast<Origin>(oPos));

	//Return Stream
	return stream;
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

void Drawables::D_RoundedRectangle::initD_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos)
{
	//Init Corner Rounding
	cornerRounding = rounding;

	//Construct Rounded Rect
	constructRoundedRect(color, size, pos, cornerRounding, rotation, oPos);
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
		setPointCount(RECT_EDGES * ROUNDING_POINTS_PER_EDGE);
		rectTotalPoints.reserve(RECT_EDGES * ROUNDING_POINTS_PER_EDGE);

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

sf::Vector2f Drawables::D_RoundedRectangle::getSize() const {
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

void Drawables::D_RoundedRectangle::Custom_Draw() const {
	exEvents->window.draw(*this);
}

std::string Drawables::D_RoundedRectangle::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_Base<sf::ConvexShape>::serialize() << " " << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << " " << getFillColor().a << " "
		<< getSize().x << " " << getSize().y << " " << getPosition().x << " " << getPosition().y << " "
		<< getCornerRounding() << " " << getRotation() << " " << static_cast<int>(Custom_GetOrigin()) << " "
		<< getOutlineColor().r << " " << getOutlineColor().g << " " << getOutlineColor().b << " " << getOutlineColor().a << " "
		<< getOutlineThickness() << " " << getScale().x << " " << getScale().y;

	return oss.str();
}

void Drawables::D_RoundedRectangle::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	;
	sf::Color color;
	sf::Vector2f size;
	sf::Vector2f pos;
	float rounding;
	float rotation;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::ConvexShape>::deserialize(iss) >> color.r >> color.g >> color.b >> color.a
		>> size.x >> size.y >> pos.x >> pos.y >> rounding 
		>> rotation >> oPos >> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	constructRoundedRect(color, size, pos, rounding, rotation, static_cast<Origin>(oPos));

	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);
}

std::istringstream& Drawables::D_RoundedRectangle::deserialize(std::istringstream& stream) {
	//Temporary Variables
	;
	sf::Color color;
	sf::Vector2f size;
	sf::Vector2f pos;
	float rounding;
	float rotation;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::ConvexShape>::deserialize(stream) >> color.r >> color.g >> color.b >> color.a
		>> size.x >> size.y >> pos.x >> pos.y >> rounding
		>> rotation >> oPos >> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	constructRoundedRect(color, size, pos, rounding, rotation, static_cast<Origin>(oPos));

	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);

	return stream;
}

// ================================================================================
// Rectangle Shape Initializer
// ================================================================================

Drawables::D_Rectangle::D_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
	: D_Base<RectangleShape>()
{
	//Set Drawables Components
	setFillColor(color);
	setSize(size);
	setPosition(pos);
	setRotation(rotation);

	//Set Origin
	Custom_SetOrigin(oPos);
}

void Drawables::D_Rectangle::initD_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	setFillColor(color);
	setSize(size);
	setPosition(pos);
	setRotation(rotation);

	//Set Origin
	Custom_SetOrigin(oPos);
}

void Drawables::D_Rectangle::Custom_Draw() const {
	exEvents->window.draw(*this);
}

std::string Drawables::D_Rectangle::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_Base<sf::RectangleShape>::serialize() << " " << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << " " << getFillColor().a << " "
		<< getSize().x << " " << getSize().y << " " << getPosition().x << " " << getPosition().y << " "
		<< getRotation() << " " << static_cast<int>(Custom_GetOrigin()) << " "
		<< getOutlineColor().r << " " << getOutlineColor().g << " " << getOutlineColor().b << " " << getOutlineColor().a << " "
		<< getOutlineThickness() << " " << getScale().x << " " << getScale().y;

	return oss.str();
}

void Drawables::D_Rectangle::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	;
	sf::Color color;
	sf::Vector2f size;
	sf::Vector2f pos;
	float rotation;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::RectangleShape>::deserialize(iss) >> color.r >> color.g >> color.b >> color.a
		>> size.x >> size.y >> pos.x  >> pos.y >> rotation >> oPos
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	//Set Drawables Components
	setFillColor(color);
	setSize(size);
	setPosition(pos);
	setRotation(rotation);
	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));
}

std::istringstream& Drawables::D_Rectangle::deserialize(std::istringstream& stream) {
	//Temporary Variables
	;
	sf::Color color;
	sf::Vector2f size;
	sf::Vector2f pos;
	float rotation;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::RectangleShape>::deserialize(stream) >> color.r >> color.g >> color.b >> color.a
		>> size.x >> size.y >> pos.x >> pos.y >> rotation >> oPos
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	//Set Drawables Components
	setFillColor(color);
	setSize(size);
	setPosition(pos);
	setRotation(rotation);
	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));

	return stream;
}

// ================================================================================
// Circle Shape Initializer
// ================================================================================

Drawables::D_Circle::D_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
	: D_Base<CircleShape>()
{
	//Set Drawables Components
	setFillColor(color);
	setRadius(radius);
	setPosition(pos);
	setRotation(rotation);

	//Set Origin
	Custom_SetOrigin(oPos);
}

void Drawables::D_Circle::initD_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation, Origin oPos)
{
	//Set Drawables Components
	setFillColor(color);
	setRadius(radius);
	setPosition(pos);
	setRotation(rotation);

	//Set Origin
	Custom_SetOrigin(oPos);
}

void Drawables::D_Circle::Custom_Draw() const {
	exEvents->window.draw(*this);
}

std::string Drawables::D_Circle::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_Base<sf::CircleShape>::serialize() << " " << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << " " << getFillColor().a << " "
		<< getRadius() << " " << getPosition().x << " " << getPosition().y << " " << getRotation() << " " 
		<< getPointCount() << " " << static_cast<int>(Custom_GetOrigin()) << " "
		<< getOutlineColor().r << " " << getOutlineColor().g << " " << getOutlineColor().b << " " << getOutlineColor().a << " "
		<< getOutlineThickness() << " " << getScale().x << " " << getScale().y;

	return oss.str();
}

void Drawables::D_Circle::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	sf::Color color;
	float radius;
	sf::Vector2f pos;
	float rotation;
	size_t pointcount;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::CircleShape>::deserialize(iss) >> color.r >> color.g >> color.b >> color.a
		>> radius >> pos.x >> pos.y >> rotation >> pointcount >> oPos
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	//Set Drawables Components
	setFillColor(color);
	setRadius(radius);
	setPosition(pos);
	setRotation(rotation);
	setPointCount(pointcount);
	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));
}

std::istringstream& Drawables::D_Circle::deserialize(std::istringstream& stream) {
	//Temporary Variables
	sf::Color color;
	float radius;
	sf::Vector2f pos;
	float rotation;
	size_t pointcount;
	int oPos;
	sf::Color outlinecolor;
	float outlinethickness;
	sf::Vector2f scale;

	//Input Stream From String
	D_Base<sf::CircleShape>::deserialize(stream) >> color.r >> color.g >> color.b >> color.a
		>> radius >> pos.x >> pos.y >> rotation >> pointcount >> oPos
		>> outlinecolor.r >> outlinecolor.g >> outlinecolor.b >> outlinecolor.a
		>> outlinethickness >> scale.x >> scale.y;

	//Set Drawables Components
	setFillColor(color);
	setRadius(radius);
	setPosition(pos);
	setRotation(rotation);
	setPointCount(pointcount);
	setOutlineColor(outlinecolor);
	setOutlineThickness(outlinethickness);
	setScale(scale);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));

	return stream;
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

void Drawables::D_Sprite::initD_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation, sf::Uint8 opacity, Origin oPos)
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

void Drawables::D_Sprite::Custom_SetGlobalSize(sf::Vector2f const& size) {
	setScale(size.x / getLocalBounds().getSize().x, size.y / getLocalBounds().getSize().y);
}

void Drawables::D_Sprite::Custom_Draw() const {
	exEvents->window.draw(*this);

}

std::string Drawables::D_Sprite::serialize() const {
	std::ostringstream oss;

	//Output Stream From String
	oss << D_Base<sf::Sprite>::serialize() << " " << getTextureRect().left << " " << getTextureRect().top << " " << getTextureRect().width << " " << getTextureRect().height << " "
		<< getScale().x << " " << getScale().y << " " << getPosition().x << " " << getPosition().y << " " << getRotation() << " "
		<< getColor().r << " " << getColor().g << " " << getColor().b << " " << getColor().a << " " << static_cast<int>(Custom_GetOrigin());

	return oss.str();
}

void Drawables::D_Sprite::deserialize(std::string const& data) {
	std::istringstream iss(data);

	//Temporary Variables
	sf::IntRect texrect;
	sf::Vector2f scale;
	sf::Vector2f pos;
	float rotation;
	sf::Color color;
	int oPos;

	//Input Stream From String
	D_Base<sf::Sprite>::deserialize(iss) >> texrect.left >> texrect.top >> texrect.width >> texrect.height
		>> scale.x >> scale.y >> pos.x >> pos.y >> rotation >> color.r >> color.g >> color.b >> color.a
		>> oPos;

	//Set Drawables Components
	setTextureRect(texrect);
	setScale(scale);
	setPosition(pos);
	setRotation(rotation);
	setColor(color);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));
}

std::istringstream& Drawables::D_Sprite::deserialize(std::istringstream& stream) {
	//Temporary Variables
	sf::IntRect texrect;
	sf::Vector2f scale;
	sf::Vector2f pos;
	float rotation;
	sf::Color color;
	int oPos;

	//Input Stream From String
	D_Base<sf::Sprite>::deserialize(stream) >> texrect.left >> texrect.top >> texrect.width >> texrect.height
		>> scale.x >> scale.y >> pos.x >> pos.y >> rotation >> color.r >> color.g >> color.b >> color.a
		>> oPos;

	//Set Drawables Components
	setTextureRect(texrect);
	setScale(scale);
	setPosition(pos);
	setRotation(rotation);
	setColor(color);

	//Set Origin
	Custom_SetOrigin(static_cast<Origin>(oPos));

	return stream;
}
