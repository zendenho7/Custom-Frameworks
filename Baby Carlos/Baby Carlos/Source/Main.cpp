
/*****************************************************************************************************************
@file         main.cpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This file is the point of compilation for all pch.hpp include files

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\Header\pch.hpp"
#include "..\Header\Systems.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    //Create Debugging Console
    CreateConsole(true);
    
    //Window System Init
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Baby Carlos", sf::Style::Default);

    //Set Systems Icon
    SetIcon(hInstance, window.getSystemHandle());

    //Shape Init
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {

                // Free the console before exiting
                if (GetConsoleWindow()) {
                    FreeConsole();
                }

                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}