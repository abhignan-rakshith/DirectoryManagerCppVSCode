#include "UserInterface.h"
#include <iostream>
#include <string>

UserInterface::UserInterface() : dirCreator(std::make_unique<DirectoryCreator>()),
                                 dirCopier(nullptr)
{ // Initialize as nullptr, create only when needed
}

void UserInterface::run()
{
    displayWelcome();

    int choice = getUserChoice();

    switch (choice)
    {
    case 1:
        dirCreator->createDirectoryStructure();
        offerToCopyAfterCreation();
        break;
    case 2:
        try
        {
            // Only create the DirectoryCopier when needed
            if (!dirCopier)
            {
                dirCopier = std::make_unique<DirectoryCopier>();
            }
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

    displayGoodbye();
}

void UserInterface::displayWelcome()
{
    std::cout << "Welcome player!" << std::endl;
    std::cout << "What do you want to do today?" << std::endl;
}

int UserInterface::getUserChoice()
{
    std::cout << "Choose from below:" << std::endl;
    std::cout << "1. Create folder structure" << std::endl;
    std::cout << "2. Copy files from root dir" << std::endl;

    std::string input;
    std::getline(std::cin, input);

    try
    {
        return std::stoi(input);
    }
    catch (...)
    {
        return 0; // Invalid choice
    }
}

void UserInterface::displayGoodbye()
{
    std::cout << "\nBye!" << std::endl;
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

    std::cout << "\nFinished creating the sub dir inside the stem dir provided..." << std::endl;
    std::cout << "Does Player want to proceed with copying files from the root dir? (y/n): ";

    std::string response;
    std::getline(std::cin, response);

    if (response == "y" || response == "Y")
    {
        try
        {
            // Create the DirectoryCopier if it doesn't exist
            if (!dirCopier)
            {
                dirCopier = std::make_unique<DirectoryCopier>();
            }

            // Copy files to the stem directory
            bool success = dirCopier->copyFilesToSpecificStemDir(stemDir);

            if (success)
            {
                std::cout << "Successfully copied the files into every sub directory of the stem dir!" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Ok, I won't do that." << std::endl;
    }
}
