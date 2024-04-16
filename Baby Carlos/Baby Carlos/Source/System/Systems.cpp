
#include "..\..\Header\System\pch.hpp"
#include "..\..\Resource\resource.h"
#include "..\..\Header\System\Systems.hpp"

// ================================================================================
// Function: Constructors Window & Event Handler
// ================================================================================

Systems::WindowHandler::WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : window(mode, title, style, settings) {}

Systems::EventHandler::EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : triggered{ false }, event{ sf::Event() }, WindowHandler(mode, title, style, settings) {}

// ================================================================================
// Function: System Input Handling
// ================================================================================

void Systems::WindowHandler::CreateConsole(bool debugging) {
    if (debugging) {
        // Attach Console For Debugging
        if (!AttachConsole(ATTACH_PARENT_PROCESS))
        {
            // If attaching fails, create a new console.
            AllocConsole();
        }

        // Redirect std::cout and std::cerr to the console
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);
        freopen_s(&stream, "CONOUT$", "w", stderr);

        std::cout << "Console Output For Debugging" << std::endl;
        std::cin.get();
    }
}

void Systems::WindowHandler::SetIcon(HINSTANCE const& hInstance) {
    //Set Icon For Window
    if (window.getSystemHandle()) {
        HICON hMyIcon{ LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)) };
        SendMessage(window.getSystemHandle(), WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
        SendMessage(window.getSystemHandle(), WM_SETICON, ICON_SMALL, (LPARAM)hMyIcon);
    }
}

// ================================================================================
// Function: Events Polling
// ================================================================================

bool Systems::EventHandler::pollEvents() {

    //Poll Events
    bool result{ window.pollEvent(event) };

    //Check For Escaping Application Events
    if ((event.type == sf::Event::Closed || keyTriggered(sf::Keyboard::Scancode::Escape)) && result) {

        // Free the console before exiting
        if (GetConsoleWindow()) {
            FreeConsole();
        }

        window.close();
    }

    //Return True If There Are Events
    return result;
}

// ================================================================================
// Function: System Input Handling
// ================================================================================

bool Systems::EventHandler::keyTriggered(sf::Keyboard::Scancode keycode) {

    //Reset Boolean When Key Released
    if (keyReleased(keycode)) {
        triggered = false;
    }

    //Check If Key Triggered
    if (keyChecked(keycode) && !triggered) {
        triggered = true;
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::keyChecked(sf::Keyboard::Scancode keycode) {

    //Check If Key Checked
    if (sf::Keyboard::isKeyPressed(keycode)) {
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::keyReleased(sf::Keyboard::Scancode keycode) {

    //Check For Key Released
    if (event.type == sf::Event::KeyReleased && event.key.scancode == keycode) {
        return true;
    }
    else {
        return false;
    }
}
