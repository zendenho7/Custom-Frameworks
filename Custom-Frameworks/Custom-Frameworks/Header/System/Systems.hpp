/*****************************************************************************************************************
@file         Systems.hpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains the declarations of objects used to manage the application systems

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

namespace Systems {

	// ================================================================================
	// Class: Window Handler
	// ================================================================================
	class WindowHandler {
	public:
		//System Window
		sf::RenderWindow window;

		//Frequently Used Window Components
		sf::Vector2f windowSize;
		sf::Vector2f windowCenter;

		//Default Constructor
		WindowHandler() : window(), windowSize(), windowCenter(){}

		/// <summary>
		/// WindowHandler Constructor
		/// </summary>
		/// <param name="mode">: Size Of Window</param>
		/// <param name="title">: Title Of Window</param>
		/// <param name="style">: Window Style</param>
		/// <param name="settings">: Window Settings</param>
		WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		//Create Console
		void CreateConsole(bool debugging);

		//Set Icon Based On Loaded Resource
		void SetIcon(HINSTANCE const& hInstance);

		//Virtual Destructor
		virtual ~WindowHandler() = default;
	};

	// ================================================================================
	// Class: Event Handler Derived From WindowHandler
	// ================================================================================
	class EventHandler : public WindowHandler {
	private:
		//Input Handling For Events
		bool b_mouseTriggered;
		bool b_mouseReleased;
		bool b_keyTriggered;
		bool b_keyReleased;
	public:
		//System Events
		sf::Event event;

		//Default Constructor
		EventHandler() : WindowHandler(), b_mouseTriggered{ false }, b_mouseReleased{ false }, b_keyTriggered{ false }, b_keyReleased{ false }, event() {}

		/// <summary>
		/// EventHandler Constructor ( Contains Window Handler & Other Event Functions )
		/// </summary>
		/// <param name="mode">: Size Of Window</param>
		/// <param name="title">: Title Of Window</param>
		/// <param name="style">: Window Style</param>
		/// <param name="settings">: Window Settings</param>
		EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		//Poll Events ( Input etc. )
		void pollEvents();

		//Custom Events Input Handling
		bool keyTriggered(sf::Keyboard::Scancode keycode);
		bool keyChecked(sf::Keyboard::Scancode keycode);
		bool keyReleased(sf::Keyboard::Scancode keycode);

		bool mouseTriggered(sf::Mouse::Button btncode);
		bool mouseChecked(sf::Mouse::Button btncode);
		bool mouseReleased(sf::Mouse::Button btncode);

		//Destructor
		~EventHandler() override = default;
	};

	// ================================================================================
	// Class: Frame & Time Handling
	// ================================================================================
	class FrameTime {
	private:

		//Time Calculation & Management
		sf::Clock clock;
		sf::Time currTime;
		sf::Time prevTime;

		//Elapsed Time
		sf::Time elapsedTime;

		//Elapsed Frame
		int elapsedFrame;

		//Frame Rate
		float frameRate;

		//Delta Time
		float deltaTime;
	public:

		//Default Constructor
		FrameTime() : clock(), currTime(clock.getElapsedTime()), prevTime(clock.getElapsedTime()), elapsedTime(clock.getElapsedTime()), elapsedFrame{0}, frameRate{0.0f}, deltaTime{0.0f} {}
		
		//Update Time & Frame Components
		bool UpdateFrameTime(unsigned int targetFPS);

		//Get Frame Rate
		float getFrameRate() const;

		//Get Delta Time
		float getDeltaTime() const;
	};
}

#endif // !SYSTEMS_HPP
