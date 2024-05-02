/*****************************************************************************************************************
@file         main.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file is the starting point of the application

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\System\GameStateManager.hpp"
#include "..\..\Header\System\Systems.hpp"
#include "..\..\Header\System\Load.hpp"

// ================================================================================
// EXTERNALS
// ================================================================================

Systems::EventHandler* exEvents;
Systems::FrameTime* exTime;
Load::Assets* exAssets;
GSManager::GameStateManager* exGSManager;

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

    //If Debug Mode, Create Console
    //#ifdef _DEBUG
    //    exEvents->CreateConsole(true);
    //#endif // _DEBUG
    exEvents->CreateConsole(true);

    //Initialize Event Handler & Create Window
    exEvents = new Systems::EventHandler(sf::VideoMode(1600, 900), "Custom Frameworks", sf::Style::Default);
    exEvents->SetIcon(hInstance);

    //Initialize Time Handler
    exTime = new Systems::FrameTime();

    //Initialize Assets Handler
    exAssets = new Load::Assets();

    //Initialize GameState
    exGSManager = new GSManager::GameStateManager(GSManager::GSTypes::GS_SPLASHSCREEN);

    //Game Loop
    while (exGSManager->getGameRunning())
    {
        //Time Step
        while (exTime->UpdateFrameTime(60));

        //Input Checks
        exEvents->pollEvents();

        //Update GameState
        exGSManager->updateGameState();

        //Draw GameState
        exGSManager->drawGameState();

        //Display Window Contents
        exEvents->window.display();
    }

    //Delete Singletons
    delete exEvents;
    delete exTime;
    delete exAssets;
    delete exGSManager;

    return 0;
}