/*****************************************************************************************************************
@file         main.cpp
@project      SUPER CARLOS
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
    systemEvents->window.setFramerateLimit(60);

    //Initialize Time Keeper
    timeKeeper = new Systems::FrameTime();

    //Initialize GameState
    GSManager::GameStateInit(GSManager::GS_SPLASH_SCREEN);

    //Game Loop
    while (GSCurrent != GSManager::GS_EXIT)
    {
        //Check If GameState Is Restarted
        if (GSCurrent == GSManager::GS_RESTART) {
            GSCurrent = GSPrevious;
            GSNext = GSPrevious;
        }
        else {
            //Load & Update GameState
            GSManager::GameStateUpdate();
            fpLoad();
        }

        //Init GameState
        fpInit();

        //Game Update & Draw Loop
        while (GSCurrent == GSNext) {

            //Input Checks
            systemEvents->pollEvents();
            
            //Update GameState
            fpUpdate();

            //Draw GameState
            fpDraw();

            //Display Window Contents
            systemEvents->window.display();

            //Update Time
            timeKeeper->UpdateFrameTime();
        }

        //Free GamState
        fpFree();

        //If Not Restart Unload
        if (GSNext != GSManager::GS_RESTART) {
            fpUnload();
        }

        //Store Previous & Set Current
        GSPrevious = GSCurrent;
        GSCurrent = GSNext;
    }
    
    //Destroy Event Handler
    delete systemEvents;
    delete timeKeeper;

    return 0;
}