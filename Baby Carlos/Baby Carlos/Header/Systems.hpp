
#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

namespace Systems {

	//Window Handling
	class WindowHandler {
	public:
		//System Window
		sf::RenderWindow window;

		//Constructor
		WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		void CreateConsole(bool debugging);

		void SetIcon(HINSTANCE const& hInstance);

		virtual ~WindowHandler(){}
	};

	//Events Handling
	class EventHandler : public WindowHandler {
	private:
		//Input Handling For Events
		bool triggered;
	public:
		//System Events
		sf::Event event;

		//Constructor
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
