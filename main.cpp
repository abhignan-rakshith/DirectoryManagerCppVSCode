#include "UserInterface.h"
#include <iostream>

int main()
{
    try
    {
        UserInterface ui;
        ui.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
