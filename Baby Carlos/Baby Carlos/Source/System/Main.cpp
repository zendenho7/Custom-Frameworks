
/*****************************************************************************************************************
@file         main.cpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This file is the point of compilation for all pch.hpp include files

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Systems.hpp"

Systems::EventHandler* systemEvents;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    //Initialize Systems & Events
    systemEvents->CreateConsole(true);
    systemEvents = new Systems::EventHandler(sf::VideoMode(1600, 900), "Baby Carlos", sf::Style::Default);
    systemEvents->SetIcon(hInstance);

    //Shape Init
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (systemEvents->window.isOpen())
    {
        while (systemEvents->pollEvents()) {

            if (systemEvents->keyTriggered(sf::Keyboard::Scancode::A)) {
                std::cout << systemEvents->event.key.scancode << '\n';
            }
        }

        systemEvents->window.clear();
        systemEvents->window.draw(shape);
        systemEvents->window.display();
    }

    //Delete Window System Events
    delete systemEvents;

    return 0;
}