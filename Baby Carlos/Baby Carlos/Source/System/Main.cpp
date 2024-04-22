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
    exSystemEvents->CreateConsole(true);
    exSystemEvents = new Systems::EventHandler(sf::VideoMode(1600, 900), "Baby Carlos", sf::Style::Default);
    exSystemEvents->SetIcon(hInstance);
    exSystemEvents->window.setFramerateLimit(60);

    //Initialize Time Keeper
    exTimeKeeper = new Systems::FrameTime();

    //Initialize Assets Handler
    exAssets = new Load::Assets;

    //Initialize GameState
    GSManager::GameStateInit(GSManager::GS_SPLASH_SCREEN);

    //Game Loop
    while (exGSCurrent != GSManager::GS_EXIT)
    {
        //Check If GameState Is Restarted
        if (exGSCurrent == GSManager::GS_RESTART) {
            exGSCurrent = exGSPrevious;
            exGSNext = exGSPrevious;
        }
        else {
            //Load & Update GameState
            GSManager::GameStateUpdate();
            exFPLoad();
        }

        //Init GameState
        exFPInit();

        //Game Update & Draw Loop
        while (exGSCurrent == exGSNext) {

            //Clear Window
            exSystemEvents->window.clear();

            //Input Checks
            exSystemEvents->pollEvents();
            
            //Update GameState
            exFPUpdate();

            //Draw GameState
            exFPDraw();

            //Display Window Contents
            exSystemEvents->window.display();

            //Update Time
            exTimeKeeper->UpdateFrameTime();
        }

        //Free GamState
        exFPFree();

        //If Not Restart Unload
        if (exGSNext != GSManager::GS_RESTART) {
            exFPUnload();
        }

        //Store Previous & Set Current
        exGSPrevious = exGSCurrent;
        exGSCurrent = exGSNext;
    }
    
    //Destroy External Handlers
    delete exSystemEvents;
    delete exTimeKeeper;
    delete exAssets;

    return 0;
}