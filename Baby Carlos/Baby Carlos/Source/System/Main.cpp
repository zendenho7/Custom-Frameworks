/*****************************************************************************************************************
@file         main.cpp
@project      BABY CARLOS
@author       Zen Ho
@brief        This file is the starting point of the application

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\System\Utils.hpp"

// ================================================================================
// EXTERNALS
// ================================================================================

   Systems::EventHandler* systemEvents;

// ================================================================================
// WINMAIN ENTRY
// ================================================================================
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {

    //WinMain Unreferenced Params
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    //Check For Memory Leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //Initialize Event Handler & Create Window
    systemEvents->CreateConsole(true);
    systemEvents = new Systems::EventHandler(sf::VideoMode(1600, 900), "Baby Carlos", sf::Style::Default);
    systemEvents->SetIcon(hInstance);

    //Initialize GameState
    GSManager::GameStateInit(GSManager::GS_SPLASH_SCREEN);

    //Game Loop
    while (current != GSManager::GS_EXIT)
    {
        //Check If GameState Is Restarted
        if (current == GSManager::GS_RESTART) {
            current = previous;
            next = previous;
        }
        else {
            //Load & Update GameState
            GSManager::GameStateUpdate();
            fpLoad();
        }

        //Init GameState
        fpInit();

        //Game Update & Draw Loop
        while (current == next) {
            while (systemEvents->pollEvents()) {
                fpUpdate();
            }

            fpDraw();
        }

        //Free GamState
        fpFree();

        //If Not Restart Unload
        if (next != GSManager::GS_RESTART) {
            fpUnload();
        }

        //Store Previous & Set Current
        previous = current;
        current = next;
    }
    
    //Destroy Event Handler
    delete systemEvents;

    return 0;
}