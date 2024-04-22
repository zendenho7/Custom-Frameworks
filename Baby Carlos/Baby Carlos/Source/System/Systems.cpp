/*****************************************************************************************************************
@file         Systems.cpp
@project      SUPER CARLOS
@author       Zen Ho
@brief        This file contains the defintions of objects used to manage the application systems

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Resource\resource.h"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\System\Utils.hpp"

// ================================================================================
// EXTERNALS
// ================================================================================

Systems::EventHandler* exSystemEvents;
Systems::FrameTime* exTimeKeeper;

// ================================================================================
// Function: Constructors Window & Event Handler
// ================================================================================

Systems::WindowHandler::WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : window(mode, title, style, settings), 
    windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)),
    windowCenter(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f) {}

Systems::EventHandler::EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : bmouseTriggered{ false }, bmouseReleased{ false }, bkeyTriggered{ false }, bkeyReleased{ false }, event{ sf::Event() }, WindowHandler(mode, title, style, settings) {}

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

        //Break GameLoop
       exGSNext = GSManager::GS_EXIT;

        //Free the console before exiting (For Debugging)
        FreeConsole();

        //Close Window
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
        bkeyTriggered = false;
    }

    //Check If Key Triggered
    if (keyChecked(keycode) && !bkeyTriggered) {
        bkeyTriggered = true;
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

    //Released Flag Reset
    if (event.type != sf::Event::KeyReleased) {
        bkeyReleased = false;
    }

    //Check For Key Released
    if ((event.type == sf::Event::KeyReleased && event.key.scancode == keycode) && !bkeyReleased) {
        bkeyReleased = true;
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::mouseTriggered(sf::Mouse::Button btncode) {
    //Reset Boolean When Key Released
    if (mouseReleased(btncode)) {
        bmouseTriggered = false;
    }

    //Check If Key Triggered
    if (mouseChecked(btncode) && !bmouseTriggered) {
        bmouseTriggered = true;
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::mouseChecked(sf::Mouse::Button btncode) {
    //Check If Key Checked
    if (sf::Mouse::isButtonPressed(btncode)) {
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::mouseReleased(sf::Mouse::Button btncode) {
    //Released Flag Reset
    if (event.type != sf::Event::MouseButtonReleased) {
        bmouseReleased = false;
    }

    //Check For Key Released
    if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == btncode) && !bmouseReleased) {
        bmouseReleased = true;
        return true;
    }
    else {
        return false;
    }
}

// ================================================================================
// Function: Frame & Time Handling
// ================================================================================

void Systems::FrameTime::UpdateFrameTime() {

    //Elapsed Frame & Time Calculation
    elapsedTime = clock.getElapsedTime();
    ++elapsedFrame;

    //Delta Time Calculation
    currTime = elapsedTime;
    deltaTime = currTime.asSeconds() - prevTime.asSeconds();
    prevTime = currTime;

    //FrameRate Calculation ( FPS )
    frameRate = sf::seconds(1.0f).asSeconds() / deltaTime;
}