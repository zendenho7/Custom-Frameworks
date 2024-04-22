/*****************************************************************************************************************
@file         Systems.hpp
@project      SUPER CARLOS
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

		//Constructors
		WindowHandler() : window(), windowSize(), windowCenter(){}
		WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		//Other Window Functions
		void CreateConsole(bool debugging);
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
		bool bmouseTriggered;
		bool bmouseReleased;
		bool bkeyTriggered;
		bool bkeyReleased;
	public:
		//System Events
		sf::Event event;

		//Constructors
		EventHandler() : WindowHandler(), bmouseTriggered{ false }, bmouseReleased{ false }, bkeyTriggered{ false }, bkeyReleased{ false }, event() {}
		EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		//Polling Events
		bool pollEvents();

		//Custom Events Input Handling
		bool keyTriggered(sf::Keyboard::Scancode keycode);
		bool keyChecked(sf::Keyboard::Scancode keycode);
		bool keyReleased(sf::Keyboard::Scancode keycode);

		bool mouseTriggered(sf::Mouse::Button btncode);
		bool mouseChecked(sf::Mouse::Button btncode);
		bool mouseReleased(sf::Mouse::Button btncode);
	};

	// ================================================================================
	// Class: Frame & Time Handling
	// ================================================================================

	class FrameTime {
	private:
		sf::Clock clock;
		sf::Time currTime;
		sf::Time prevTime;
	public:
		sf::Time elapsedTime;
		int elapsedFrame;

		float frameRate;
		float deltaTime;

		//Constructor
		FrameTime() : clock(), currTime(clock.getElapsedTime()), prevTime(clock.getElapsedTime()), elapsedTime(clock.getElapsedTime()), elapsedFrame{0}, frameRate{0.0f}, deltaTime{0.0f} {}
		
		//Update Time & Frame Components
		void UpdateFrameTime();
	};
}

// ================================================================================
// External System & Events Handler Object
// ================================================================================
extern Systems::EventHandler* exSystemEvents;
extern Systems::FrameTime* exTimeKeeper;

#endif // !SYSTEMS_HPP
