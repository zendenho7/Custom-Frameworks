
/*****************************************************************************************************************
@file         main.cpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This file is the point of compilation for all pch.hpp include files

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

#include "..\Header\pch.hpp"
#include "..\Resource\resource.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Baby Carlos", sf::Style::Default);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    //Set Icon For Window
    if (HWND hwnd{ window.getSystemHandle() }) {
        std::cout << "HERE" << '\n';
        HICON hMyIcon{ LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)) };
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hMyIcon);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}