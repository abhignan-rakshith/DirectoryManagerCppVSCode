#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "DirectoryCreator.h"
#include "DirectoryCopier.h"
#include <memory>

// Class for handling user interface
class UserInterface
{
private:
    std::unique_ptr<DirectoryCreator> dirCreator;
    std::unique_ptr<DirectoryCopier> dirCopier;

public:
    UserInterface();
    void run();

private:
    void displayWelcome();
    int getUserChoice();
    void displayGoodbye();
};

#endif // USER_INTERFACE_H