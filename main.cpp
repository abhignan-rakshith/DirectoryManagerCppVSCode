/**
 * Directory Template Tool - Version 5
 *
 * A console application for creating directory structures and
 * populating them with template files for C++ development.
 *
 * Features:
 * - Create numbered directory structures
 * - Create template files (main.cpp, VS Code settings)
 * - Self-contained with embedded template files
 */

#include "UserInterface.h"
#include <iostream>

int main()
{
    try
    {
        // Create and run the user interface
        UserInterface ui;
        ui.run();
    }
    catch (const std::exception &e)
    {
        // Handle any uncaught exceptions
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
