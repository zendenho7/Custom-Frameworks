
#include "..\Header\pch.hpp"
#include "..\Resource\resource.h"

void CreateConsole(bool debugging) {
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

void SetIcon(HINSTANCE const& hInstance, HWND const& hwnd) {
    //Set Icon For Window
    if (hwnd) {
        HICON hMyIcon{ LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)) };
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hMyIcon);
    }
}