/*****************************************************************************************************************
@file         Drawables.hpp
@project      Custom Frameworks
@author       Zen Ho
@brief        This is the header file for the drawables helper functions declarations

Copyright � 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

#pragma once

#ifndef DRAWABLES_HPP
#define DRAWABLES_HPP

namespace Drawables {

	// ================================================================================
	// Constants
	// ================================================================================
	const sf::Uint8  DEF_CHAR_SIZE{ 72 };

	// ================================================================================
	// Enums: Defined Origin Types
	// ================================================================================
	enum class Origin : sf::Uint8 {
		CENTER = 0,
		TOP_LEFT,
		TOP_RIGHT,
		BOT_RIGHT,
		BOT_LEFT
	};

	// ================================================================================
	// Class: Template Base Drawable
	// ================================================================================
	template<typename T>
	class D_Base : public T {
	private:
		sf::Vector2f fixedScale;

		Origin originPos;

	protected:
		//Default Consturctor
		D_Base() : fixedScale{ 1.0f, 1.0f }, originPos{ Origin::CENTER } {}

		//Default Copy Constructor
		D_Base(D_Base const& copy) = default;

		//Deleted Copy Assignment
		D_Base& operator=(D_Base const& copy) = delete;

		//Custom Draw Function
		virtual void Custom_Draw() const = 0;
	public:

		//Custom Member Functions
		void Custom_SetOrigin(Origin oPos = Origin::CENTER) {

			//Set Origin Position
			originPos = oPos;

			//Update Origin
			Custom_UpdateOrigin();
		}

		//Update Origin Pos
		void Custom_UpdateOrigin() {
			//Size Of Object
			sf::Vector2f size{ T::getLocalBounds().getSize() };

			//Switch Cases For Origin Setting
			switch (originPos) {
			case Origin::CENTER:
				T::setOrigin(size.x / 2, size.y / 2);
				break;
			case Origin::TOP_LEFT:
				T::setOrigin(0.0f, 0.0f);
				break;
			case Origin::TOP_RIGHT:
				T::setOrigin(size.x, 0.0f);
				break;
			case Origin::BOT_RIGHT:
				T::setOrigin(size.x, size.y);
				break;
			case Origin::BOT_LEFT:
				T::setOrigin(0.0f, size.y);
				break;
			default:
				break;
			}
		}

		//Set Fixed Scale ( For Size Manipulation )
		void Custom_SetFixedScale() {
			fixedScale = T::getScale();
		}

		Origin Custom_GetOrigin() const {
			return originPos;
		}

		sf::Vector2f Custom_GetOriginPosition() const{
			return T::getGlobalBounds().getPosition() + T::getOrigin();
		}

		//Get Fixed Scale
		sf::Vector2f const& Custom_GetFixedScale() const {
			return fixedScale;
		}

		//Set Opacity ( Sprite Overload )
		template<typename Q = T, typename std::enable_if<std::is_same<Q, sf::Sprite>::value, Q>::type* = nullptr>
		void Custom_SetOpacity(sf::Uint8 opacity) {
			sf::Color newColor{ Q::getColor() };
			newColor.a = opacity;
			Q::setColor(newColor);
		}

		//Set Opacity ( Shape/Text Overload )
		template<typename Q = T, typename std::enable_if<std::disjunction<std::is_same<Q, sf::Shape>, std::is_same<Q, sf::Text>>::value, Q>::type* = nullptr>
		void Custom_SetOpacity(sf::Uint8 opacity) {
			sf::Color newColor{ Q::getFillColor() };
			newColor.a = opacity;
			Q::setFillColor(newColor);
		}

		//Get Opacity ( Sprite Overload )
		template<typename Q = T, typename std::enable_if<std::is_same<Q, sf::Sprite>::value, Q>::type* = nullptr>
		sf::Uint8 Custom_GetOpacity() const {
			return T::getColor().a;
		}

		//Get Opacity ( Shape/Text Overload )
		template<typename Q = T, typename std::enable_if<std::disjunction<std::is_same<Q, sf::Shape>, std::is_same<Q, sf::Text>>::value, Q>::type* = nullptr>
		sf::Uint8 Custom_GetOpacity() const {
			return T::getFillColor().a;
		}

		//Data Serialization & Deserialization
		virtual std::string serialize() const {
			std::ostringstream oss;

			//Output Stream From String
			oss << fixedScale.x << " " << fixedScale.y << " " << static_cast<int>(originPos);

			return oss.str();
		}

		virtual void deserialize(std::string const& data) {
			std::istringstream iss(data);

			//Temporary Variables
			int tempOPos;

			//Input Stream
			iss >> fixedScale.x >> fixedScale.y >> tempOPos;

			//Set Origin Pos
			originPos = static_cast<Origin>(tempOPos);
		}

		virtual std::istringstream& deserialize(std::istringstream& stream) {
			//Temporary Variables
			int tempOPos;

			//Input Stream
			stream >> fixedScale.x >> fixedScale.y >> tempOPos;

			//Set Origin Pos
			originPos = static_cast<Origin>(tempOPos);

			return stream;
		}
	};

	// ================================================================================
	// Class: Drawable Text
	// ================================================================================

	class D_Text : public D_Base<sf::Text> {
	private:

	public:
		//Default Constructor
		D_Text();

		/// <summary>
		/// Constructor For D_Text
		/// </summary>
		/// <param name="txt">: Text String Of D_Text</param>
		/// <param name="font">: Font Of D_Text</param>
		/// <param name="color">: Color Of D_Text</param>
		/// <param name="pos">: Position Of D_Text</param>
		/// <param name="charSize">: Char Size Of D_Text (Load @ Default Size Of 72 For Higher Resolution ) | Size Can Be Changed By Scaling</param>
		/// <param name="rotation">: Rotation Of D_Text</param>
		/// <param name="oPos">: Origin Of D_Text</param>
		D_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize = DEF_CHAR_SIZE, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Default Copy Constructor
		D_Text(D_Text const& copy) = default;

		//Default Copy Assignment Operator
		D_Text& operator=(D_Text const& copy) = default;

		/// <summary>
		/// D_Text Setter
		/// </summary>
		/// <param name="txt">: Text String Of D_Text</param>
		/// <param name="font">: Font Of D_Text</param>
		/// <param name="color">: Color Of D_Text</param>
		/// <param name="pos">: Position Of D_Text</param>
		/// <param name="charSize">: Char Size Of D_Text (Load @ Default Size Of 72 For Higher Resolution) | Size Can Be Changed By Scaling</param>
		/// <param name="rotation">: Rotation Of D_Text</param>
		/// <param name="oPos">: Origin Of D_Text</param>
		void initD_Text(std::string const& txt, sf::Font const& font, sf::Color const& color, sf::Vector2f const& pos, sf::Uint8 charSize = DEF_CHAR_SIZE, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		// To Be Called Only After Setting Position
		void Custom_OffsetToCenter();

		//Custom Setting Of String
		void Custom_SetString(std::string const& txt);

		//Custom Setting Of GlobalBound Size ( Scaling To Desired Size )
		void Custom_SetGlobalSize(sf::Vector2f const& size);

		//Custom Draw Function
		virtual void Custom_Draw() const override;

		//Data Serialization & Deserialization
		virtual std::string serialize() const override;
		virtual void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};

	// ================================================================================
	// Class: Drawable Rounded Rectangle
	// ================================================================================
	class D_RoundedRectangle : public D_Base<sf::ConvexShape> {
	private:
		//Rounded Rect Constants
		const size_t	RECT_EDGES{ 4 };
		const size_t	ROUNDING_POINTS_PER_EDGE{ 10 };

		//Vertex Manager
		sf::Vector2f rectVertex[4];

		//Rounding
		float cornerRounding;

		//Update Points Positioning
		void setPoints();

		//Private Rounded Rect Constructor
		void constructRoundedRect(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding, float rotation, Origin oPos);

	public:
		//Default Constructor
		D_RoundedRectangle() : cornerRounding{ 0.0f } {}

		/// <summary>
		/// Constructor For D_RoundedRectan
		/// gle
		/// </summary>
		/// <param name="color">: Color Of Rounded Rectangle</param>
		/// <param name="size">: Size Of Rounded Rectangle</param>
		/// <param name="pos">: Position Of Rounded Rectangle</param>
		/// <param name="rounding">: Rounding Size Of Rounded Rectangle</param>
		/// <param name="rotation">: Rotation Of Rounded Rectangle</param>
		/// <param name="oPos">: Origin Of Rounded Rectangle</param>
		D_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Copy Constructor
		D_RoundedRectangle(D_RoundedRectangle const& copy) = default;

		//Copy Assignment Operator
		D_RoundedRectangle& operator=(D_RoundedRectangle const& copy) = default;

		/// <summary>
		/// D_RoundedRectangle Setter
		/// </summary>
		/// <param name="color">: Color Of Rounded Rectangle</param>
		/// <param name="size">: Size Of Rounded Rectangle</param>
		/// <param name="pos">: Position Of Rounded Rectangle</param>
		/// <param name="rounding">: Rounding Size Of Rounded Rectangle</param>
		/// <param name="rotation">: Rotation Of Rounded Rectangle</param>
		/// <param name="oPos">: Origin Of Rounded Rectangle</param>
		void initD_RoundedRectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rounding = 0.0f, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Get Size
		sf::Vector2f getSize() const;

		//Set Size
		void setSize(sf::Vector2f const& size);

		//Set Rounding
		void setCornerRounding(float rounding);

		//Get Rounding
		float getCornerRounding() const;

		//Custom Draw Function
		virtual void Custom_Draw() const override;

		//Data Serialization & Deserialization
		virtual std::string serialize() const override;
		virtual void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};

	// ================================================================================
	// Class: Drawable Rectangle
	// ================================================================================
	class D_Rectangle : public D_Base<sf::RectangleShape> {
	private:

	public:
		//Default Constructor
		D_Rectangle() = default;

		/// <summary>
		/// Constructor For D_Rectangle
		/// </summary>
		/// <param name="color">: Color Of Rectangle</param>
		/// <param name="size">: Size Of Rectangle</param>
		/// <param name="pos">: Position Of Rectangle</param>
		/// <param name="rotation">: Rotation Of Rectangle</param>
		/// <param name="oPos">: Origin Of Rectangle</param>
		D_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Default Copy Constructor
		D_Rectangle(D_Rectangle const& copy) = default;

		//Default Copy Assignment Operator
		D_Rectangle& operator=(D_Rectangle const& copy) = default;

		/// <summary>
		/// D_Rectangle Setter
		/// </summary>
		/// <param name="color">: Color Of Rectangle</param>
		/// <param name="size">: Size Of Rectangle</param>
		/// <param name="pos">: Position Of Rectangle</param>
		/// <param name="rotation">: Rotation Of Rectangle</param>
		/// <param name="oPos">: Origin Of Rectangle</param>
		void initD_Rectangle(sf::Color const& color, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Custom Draw Function
		virtual void Custom_Draw() const override;

		//Data Serialization & Deserialization
		std::string serialize() const override;
		void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};

	// ================================================================================
	// Class: Drawable Circle
	// ================================================================================
	class D_Circle : public D_Base<sf::CircleShape> {
	private:

	public:
		//Default Constructor
		D_Circle() = default;

		/// <summary>
		/// Constructor For D_Circle
		/// </summary>
		/// <param name="color">: Color Of Circle</param>
		/// <param name="radius">: Radius Of Circle</param>
		/// <param name="pos">: Position Of Circle</param>
		/// <param name="rotation">: Rotation Of Circle</param>
		/// <param name="oPos">: Origin Of Circle</param>
		D_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Default Copy Constructor
		D_Circle(D_Circle const& copy) = default;

		//Default Copy Assignment Operator
		D_Circle& operator=(D_Circle const& copy) = default;

		/// <summary>
		/// D_Circle Setter
		/// </summary>
		/// <param name="color">: Color Of Circle</param>
		/// <param name="radius">: Radius Of Circle</param>
		/// <param name="pos">: Position Of Circle</param>
		/// <param name="rotation">: Rotation Of Circle</param>
		/// <param name="oPos">: Origin Of Circle</param>
		void initD_Circle(sf::Color const& color, float radius, sf::Vector2f const& pos, float rotation = 0.0f, Origin oPos = Origin::CENTER);

		//Custom Draw Function
		void Custom_Draw() const override;

		//Data Serialization & Deserialization
		virtual std::string serialize() const override;
		virtual void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};

	// ================================================================================
	// Class: Drawable Sprite
	// ================================================================================	
	class D_Sprite : public D_Base<sf::Sprite> {
	private:

	public:
		//Default Constructor
		D_Sprite() = default;

		/// <summary>
		/// Constructor For D_Sprite
		/// </summary>
		/// <param name="tex">: Sprite Texture / SpriteSheet</param>
		/// <param name="spritePos">: Size & Position Of Texture / SpriteSheet To Assign To Sprite ( Size Based On The Sprite Size Within Spritesheet )</param>
		/// <param name="size">: Target Size For Sprite ( !!Not The Samee As The Size Specified In Spritepos )</param>
		/// <param name="pos">: Position Of Sprite</param>
		/// <param name="rotation">: Rotation Of Sprite</param>
		/// <param name="opacity">: Opacity Of Sprite</param>
		/// <param name="oPos">: Origin Of Sprite</param>
		D_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);

		//Default Copy Constructor
		D_Sprite(D_Sprite const& copy) = default;

		//Default Copy Assignment Operator
		D_Sprite& operator=(D_Sprite const& copy) = default;

		/// <summary>
		/// D_Sprite Setter
		/// </summary>
		/// <param name="tex">: Sprite Texture / SpriteSheet</param>
		/// <param name="spritePos">: Size & Position Of Texture / SpriteSheet To Assign To Sprite ( Size Based On The Sprite Size Within Spritesheet )</param>
		/// <param name="size">: Target Size For Sprite ( !!Not The Samee As The Size Specified In Spritepos )</param>
		/// <param name="pos">: Position Of Sprite</param>
		/// <param name="rotation">: Rotation Of Sprite</param>
		/// <param name="opacity">: Opacity Of Sprite</param>
		/// <param name="oPos">: Origin Of Sprite</param>
		void initD_Sprite(sf::Texture const& tex, sf::IntRect const& spritePos, sf::Vector2f const& size, sf::Vector2f const& pos, float rotation = 0.0f, sf::Uint8 opacity = 255, Origin oPos = Origin::CENTER);

		//Custom Setting Of GlobalBound Size ( Scaling To Desired Size )
		void Custom_SetGlobalSize(sf::Vector2f const& size);

		//Custom Draw Function
		void Custom_Draw() const override;

		//Data Serialization & Deserialization ( Texture Not Serialized )
		virtual std::string serialize() const override;
		virtual void deserialize(std::string const& data) override;
		virtual std::istringstream& deserialize(std::istringstream& stream) override;
	};
}

#endif // !DRAWABLES_HPP
