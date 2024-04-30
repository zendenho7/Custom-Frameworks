/*****************************************************************************************************************
@file         Systems.cpp
@project      Pathfinding Algorithms
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
#include "..\..\Header\Utility\Utils.hpp"

// ================================================================================
// Function: Constructors Window & Event Handler
// ================================================================================

Systems::WindowHandler::WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : window(mode, title, style, settings), 
    windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)),
    windowCenter(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f) {}

Systems::EventHandler::EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : WindowHandler(mode, title, style, settings), b_mouseTriggered{ false }, b_mouseReleased{ false }, b_keyTriggered{ false }, b_keyReleased{ false }, event{ sf::Event() } {}

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

void Systems::EventHandler::pollEvents() {

    //Poll Events
    while (window.pollEvent(event)) {
        //Check For Escaping Application Events
        if ((event.type == sf::Event::Closed || exGSNext == GSManager::GS_EXIT)) {

            //Break GameLoop
            exGSNext = GSManager::GS_EXIT;

            //Free the console before exiting (For Debugging)
            FreeConsole();

            //Close Window
            window.close();
        }
    }
}

// ================================================================================
// Function: System Input Handling
// ================================================================================

bool Systems::EventHandler::keyTriggered(sf::Keyboard::Scancode keycode) {

    //Reset Boolean When Key Released
    if (keyReleased(keycode)) {
        b_keyTriggered = false;
    }

    //Check If Key Triggered
    if (keyChecked(keycode) && !b_keyTriggered) {
        b_keyTriggered = true;
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
        b_keyReleased = false;
    }

    //Check For Key Released
    if ((event.type == sf::Event::KeyReleased && event.key.scancode == keycode) && !b_keyReleased) {
        b_keyReleased = true;
        return true;
    }
    else {
        return false;
    }
}

bool Systems::EventHandler::mouseTriggered(sf::Mouse::Button btncode) {
    //Reset Boolean When Key Released
    if (mouseReleased(btncode)) {
        b_mouseTriggered = false;
    }

    //Check If Key Triggered
    if (mouseChecked(btncode) && !b_mouseTriggered) {
        b_mouseTriggered = true;
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
        b_mouseReleased = false;
    }

    //Check For Key Released
    if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == btncode) && !b_mouseReleased) {
        b_mouseReleased = true;
        return true;
    }
    else {
        return false;
    }
}

// ================================================================================
// Function: Frame & Time Handling
// ================================================================================

bool Systems::FrameTime::UpdateFrameTime(unsigned int targetFPS) {

    //Elapsed Frame & Time Calculation
    elapsedTime = clock.getElapsedTime();
    ++elapsedFrame;

    //Delta Time Calculation
    currTime = elapsedTime;
    deltaTime = currTime.asSeconds() - prevTime.asSeconds();

    //FrameRate Calculation ( FPS )
    frameRate = sf::seconds(1.0f).asSeconds() / deltaTime;

    //Time Step
    if (deltaTime < (1.0f / targetFPS)) {
        return true;
    }
    else {
        prevTime = currTime;
        return false;
    }
}

float Systems::FrameTime::getFrameRate() const {
    return frameRate;
}

float Systems::FrameTime::getDeltaTime() const {
    return deltaTime;
}
