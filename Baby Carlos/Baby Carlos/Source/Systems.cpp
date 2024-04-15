
#include "..\Header\pch.hpp"

void CreateConsole() {
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