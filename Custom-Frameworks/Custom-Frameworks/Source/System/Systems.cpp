/*****************************************************************************************************************
@file         Systems.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains the defintions of objects used to manage the application systems

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Resource\resource.h"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\Utility\Utils.hpp"

// ================================================================================
// Class: Constructors Window & Event Handler
// ================================================================================

Systems::WindowHandler::WindowHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : window(mode, title, style, settings), 
    windowSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)),
    windowCenter(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f) {}

void Systems::WindowHandler::windowUpdate() {
    windowSize = { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
    windowCenter = { static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f };
}

Systems::EventHandler::EventHandler(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    : WindowHandler(mode, title, style, settings), b_mouseTriggered{ false }, b_mouseReleased{ false }, b_keyTriggered{ false }, b_keyReleased{ false }, event() {}

// ================================================================================
// Class: System Input Handling
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
// Class: Game Loop
// ================================================================================

void Systems::EventHandler::gameLoop() {

    //Init GameStateUpdate Flag
    bool gameStateUpdated{ false };

    //Poll Events
    while (window.pollEvent(event)) {

        //Update Existing Events
        eventsUpdate();

        //Check For Escaping Application Events
        if ((event.type == sf::Event::Closed || !exGSManager->getGameRunning())) {

            //Exit Game
            exGSManager->exitGame();

            //Free the console before exiting (For Debugging)
            FreeConsole();

            //Close Window
            window.close();
        }

        //Time Step
        while (exTime->UpdateTimeHandler(60));

        //Update GameState
        exGSManager->updateGameState();

        //Draw GameState
        exGSManager->drawGameState();

        //Display Window Contents
        exEvents->window.display();

        //Set GameState Updated
        gameStateUpdated = true;
    }

    //No Active Events To Poll
    if (!gameStateUpdated) {
        //Time Step
        while (exTime->UpdateTimeHandler(60));

        //Update GameState
        exGSManager->updateGameState();

        //Draw GameState
        exGSManager->drawGameState();

        //Display Window Contents
        exEvents->window.display();
    }
}

// ================================================================================
// Class: System Input Handling
// ================================================================================

bool Systems::EventHandler::keyTriggered(sf::Keyboard::Scancode keycode) {

    //Check If Key Triggered
    if (sf::Keyboard::isKeyPressed(keycode) && !b_keyTriggered) {
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
    if (event.key.scancode != keycode) {
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

    //Check If Mouse Triggered
    if (sf::Mouse::isButtonPressed(btncode) && !b_mouseTriggered) {
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
    if (event.mouseButton.button != btncode) {
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

void Systems::EventHandler::eventsUpdate() {

    //Reset Boolean When Key Released
    if (event.type == sf::Event::KeyReleased) {
        b_keyTriggered = false;
    }

    //Released Flag Reset
    if (event.type != sf::Event::KeyReleased) {
        b_keyReleased = false;
    }

    //Reset Boolean When Mouse Released
    if (event.type == sf::Event::MouseButtonReleased) {
        b_mouseTriggered = false;
    }

    //Released Flag Reset
    if (event.type != sf::Event::MouseButtonReleased) {
        b_mouseReleased = false;
    }
}

// ================================================================================
// Class: Frame & Time Handling
// ================================================================================
void Systems::TimeHandler::setDisplay(sf::Font const& font, sf::Color const& color, Drawables::Origin oPos) {
    //FPS Display
    fpsDisplay.initD_Text(std::to_string(frameRate), font, color, sf::Vector2f(0.0f, 0.0f), Drawables::DEF_CHAR_SIZE, 0.0f, oPos);
    fpsDisplay.setScale(0.4f, 0.4f);
    fpsDisplay.Custom_SetFixedScale();

    if (fpsDisplay.Custom_GetOrigin() == Drawables::Origin::CENTER)
        fpsDisplay.Custom_OffsetToCenter();

    //DeltaTime Display
    deltaTimeDisplay.initD_Text(std::to_string(deltaTime), font, color, sf::Vector2f(0.0f, 0.0f), Drawables::DEF_CHAR_SIZE, 0.0f, oPos);
    deltaTimeDisplay.setScale(0.4f, 0.4f);
    deltaTimeDisplay.Custom_SetFixedScale();

    if(deltaTimeDisplay.Custom_GetOrigin() == Drawables::Origin::CENTER)
        deltaTimeDisplay.Custom_OffsetToCenter();
}

void Systems::TimeHandler::setDisplayPos(sf::Vector2f const& pos) {
    fpsDisplay.setPosition(pos);
    deltaTimeDisplay.setPosition(pos);
}

bool Systems::TimeHandler::UpdateTimeHandler(unsigned int targetFPS) {

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

float Systems::TimeHandler::getFrameRate() const {
    return frameRate;
}

float Systems::TimeHandler::getDeltaTime() const {
    return deltaTime;
}

void Systems::TimeHandler::displayFrameRate() {
    //Update FPS Display
    fpsDisplay.Custom_SetString(std::to_string(frameRate));

    //Draw FPS Display
    exEvents->window.draw(fpsDisplay);
}

void Systems::TimeHandler::displayDeltaTime() {
    //Update DeltaTime Display
    deltaTimeDisplay.Custom_SetString(std::to_string(deltaTime));

    //Draw DeltaTime Display
    exEvents->window.draw(deltaTimeDisplay);
}

// ================================================================================
// Class: Data Handler
// ================================================================================

Systems::DataHandler::DataHandler()
    : exePath("")
{
    char buffer[MAX_PATH];
    DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (length == 0) {
        throw std::runtime_error("Failed to get executable path.");
    }
    std::string path(buffer);
    size_t pos = path.find_last_of("\\/");
    exePath = path.substr(0, pos) + "\\Assets\\Save Files\\";
}

void Systems::DataHandler::addPath(std::string const& identifier) {
    bool duplicate{ false };
    for (std::pair<std::string, std::string> const& path : dataPaths) {
        if (path.second == exePath + identifier + ".txt")
            duplicate = true;
    }

    if (!duplicate) {
        dataPaths.emplace(identifier, exePath + identifier + ".txt");
        std::cout << "Path Added: " << dataPaths.at(identifier) << '\n';
    }
    else {
        std::cout << "Path Already Exists: " << dataPaths.at(identifier) << '\n';
    }
}

std::vector<std::string> Systems::DataHandler::loadMultipleData(std::string const& identifier) {
    std::ifstream fileStream;
    fileStream.open(dataPaths.at(identifier));

    //String Data
    std::vector<std::string> datas;
    std::string data;

    if (fileStream.is_open()) {
        while (std::getline(fileStream, data)) {
            if (!data.empty()) {
                datas.push_back(data);
            }
        }

        //Close FileStream
        fileStream.close();
    }
    else {
        std::ofstream createFile;
        createFile.open(dataPaths.at(identifier));

        if(!createFile.is_open())
        std::cerr << "Error Opening Data Path To Load Data: " << dataPaths.at(identifier) << '\n';

        createFile.close();
    }

    return datas;
}

void Systems::DataHandler::saveMultipleData(std::string const& identifier, std::vector<std::string> const& serializedData) {
    std::ofstream fileStream;
    fileStream.open(dataPaths.at(identifier));

    if (fileStream.is_open()) {
        for (std::string const& data : serializedData) {
            fileStream << data << '\n';
        }

        //Close FileStream
        fileStream.close();
    }
    else {
        std::cerr << "Error Opening Data Path To Save Data: " << dataPaths.at(identifier) << '\n';
    }
}

std::string Systems::DataHandler::loadSingularData(std::string const& identifier) {
    std::ifstream fileStream;
    fileStream.open(dataPaths.at(identifier));

    //String Data
    std::string data;

    if (fileStream.is_open()) {
        std::getline(fileStream, data);

        //Close FileStream
        fileStream.close();
    }
    else {
        std::ofstream createFile;
        createFile.open(dataPaths.at(identifier));

        if (!createFile.is_open())
            std::cerr << "Error Opening Data Path To Load Data: " << dataPaths.at(identifier) << '\n';

        createFile.close();
    }

    return data;
}

void Systems::DataHandler::saveSingularData(std::string const& identifier, std::string const& serializedData) {
    std::ofstream fileStream;
    fileStream.open(dataPaths.at(identifier));

    if (fileStream.is_open()) {
        fileStream << serializedData;

        //Close FileStream
        fileStream.close();
    }
    else {
        std::cerr << "Error Opening Data Path To Save Data: " << dataPaths.at(identifier) << '\n';
    }
}
