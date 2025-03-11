#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "DirectoryCreator.h"
#include "DirectoryCopier.h"
#include <memory>

/**
 * @brief Class for handling user interaction
 *
 * UserInterface manages the application's user interaction, menu display,
 * and coordinates between different components of the system.
 */
class UserInterface
{
private:
    std::unique_ptr<DirectoryCreator> dirCreator; // For directory creation operations
    std::unique_ptr<DirectoryCopier> dirCopier;   // For template file operations

public:
    /**
     * @brief Constructor initializes components
     */
    UserInterface();

    /**
     * @brief Main entry point for running the application
     *
     * Displays the menu, handles user input, and coordinates operations.
     */
    void run();

private:
    /**
     * @brief Displays the welcome message and title
     */
    void displayWelcome();

    /**
     * @brief Gets the user's choice from the main menu
     *
     * @return int The option number chosen by the user
     */
    int getUserChoice();

    /**
     * @brief Displays the goodbye message
     */
    void displayGoodbye();

    /**
     * @brief Offers to copy template files after directory creation
     *
     * Called after directory creation to ask if the user wants to
     * create template files in the newly created directories.
     */
    void offerToCopyAfterCreation();
};

#endif // USER_INTERFACE_H