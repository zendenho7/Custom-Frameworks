/*****************************************************************************************************************
@file         Systems.hpp
@project      BABY CARLOS
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

		//Constructors
		WindowHandler() : window() {}
		WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		void CreateConsole(bool debugging);

		void SetIcon(HINSTANCE const& hInstance);

		//Virtual Destructor
		virtual ~WindowHandler(){}
	};

	// ================================================================================
	// Class: Event Handler Derived From WindowHandler
	// ================================================================================
	class EventHandler : public WindowHandler {
	private:
		//Input Handling For Events
		bool triggered;
	public:
		//System Events
		sf::Event event;

		//Constructors
		EventHandler() : WindowHandler(), triggered{ false }, event() {}
		EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		//Polling Events
		bool pollEvents();

		//Custom Events Input Handling
		bool keyTriggered(sf::Keyboard::Scancode keycode);
		bool keyChecked(sf::Keyboard::Scancode keycode);
		bool keyReleased(sf::Keyboard::Scancode keycode);
	};
}

#endif // !SYSTEMS_HPP
