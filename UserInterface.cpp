#include "UserInterface.h"
#include <iostream>
#include <string>
#include <limits> // For input validation

UserInterface::UserInterface() : dirCreator(std::make_unique<DirectoryCreator>()),
                                 dirCopier(nullptr)
{ // Initialize as nullptr, create only when needed
}

void UserInterface::run()
{
    // Show welcome message
    displayWelcome();

    // Get user choice from menu
    int choice = getUserChoice();

    // Process user choice
    switch (choice)
    {
    case 1:
        // Create directory structure
        dirCreator->createDirectoryStructure();

        // Offer to create template files
        offerToCopyAfterCreation();
        break;

    case 2:
        try
        {
            // Create the DirectoryCopier only when needed (lazy initialization)
            if (!dirCopier)
            {
                dirCopier = std::make_unique<DirectoryCopier>();
            }

            // Create template files in existing directories
            dirCopier->copyFilesToSubdirectories();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        break;

    default:
        std::cout << "Invalid choice. Exiting." << std::endl;
    }

    // Show goodbye message
    displayGoodbye();
}

void UserInterface::displayWelcome()
{
    std::cout << "====================================" << std::endl;
    std::cout << "Welcome to Directory Template Tool!" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "What do you want to do today?" << std::endl;
}

int UserInterface::getUserChoice()
{
    std::cout << "\nChoose from below:" << std::endl;
    std::cout << "  1. Create folder structure" << std::endl;
    std::cout << "  2. Create template files in existing directories" << std::endl;
    std::cout << "\nEnter your choice (1-2): ";

    // Get user input
    std::string input;
    std::getline(std::cin, input);

    // Convert to integer, with validation
    try
    {
        int choice = std::stoi(input);
        return choice;
    }
    catch (...)
    {
        // Return invalid value if conversion fails
        return 0;
    }
}

void UserInterface::displayGoodbye()
{
    std::cout << "\nThank you for using Directory Template Tool!" << std::endl;
    std::cout << "Bye!" << std::endl;
}

void UserInterface::offerToCopyAfterCreation()
{
    // Get the stem directory that was just created
    std::string stemDir = dirCreator->getLastStemDirectory();

    // If no stem directory was created (e.g., user quit), return
    if (stemDir.empty() || stemDir == "q")
    {
        return;
    }

    // Ask user if they want to create template files
    std::cout << "\nFinished creating the subdirectories inside the stem dir provided." << std::endl;
    std::cout << "Do you want to create template files in these directories? (y/n): ";

    std::string response;
    std::getline(std::cin, response);

    if (response == "y" || response == "Y")
    {
        try
        {
            // Create the DirectoryCopier if it doesn't exist (lazy initialization)
            if (!dirCopier)
            {
                dirCopier = std::make_unique<DirectoryCopier>();
            }

            // Create template files in the stem directory's subdirectories
            bool success = dirCopier->copyTemplateFilesToSpecificStemDir(stemDir);

            if (success)
            {
                std::cout << "Successfully created template files in the subdirectories!" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Ok, no template files will be created." << std::endl;
    }
}
