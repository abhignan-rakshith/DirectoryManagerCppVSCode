#include "DirectoryCreator.h"
#include <iostream>
#include <filesystem>
#include <iomanip> // For formatted output

namespace fs = std::filesystem;

DirectoryCreator::DirectoryCreator() : lastStemDirectory("")
{
    // Initialize with empty string
}

void DirectoryCreator::createDirectoryStructure()
{
    std::cout << "\nCool!, let's create the dir tree!" << std::endl;

    // Get stem directory
    std::string stemDir = getStemDirectory();
    if (stemDir == "q")
        return; // User wants to quit

    // Store the stem directory for later reference
    lastStemDirectory = stemDir;

    // Get subdirectory names
    std::vector<std::string> subDirNames = getSubdirectoryNames();
    if (subDirNames.empty())
    {
        std::cout << "No directories to create." << std::endl;
        return;
    }

    // Create the directories
    createSubdirectories(stemDir, subDirNames);

    std::cout << "Directory structure created successfully!" << std::endl;
}

std::string DirectoryCreator::getLastStemDirectory() const
{
    return lastStemDirectory;
}

std::string DirectoryCreator::getStemDirectory()
{
    // First try to get existing directory
    std::string stemDir = getValidDirectoryPath("First paste the path to the main stem dir: ");

    // If user entered 'q', return
    if (stemDir == "q")
        return "q";

    // If directory doesn't exist, ask if they want to create it
    if (!isValidDirectory(stemDir))
    {
        std::cout << "Directory doesn't exist. Create it? (y/n): ";
        std::string response;
        std::getline(std::cin, response);

        if (response == "y" || response == "Y")
        {
            try
            {
                fs::create_directories(stemDir);
                std::cout << "Created directory: " << stemDir << std::endl;
            }
            catch (const fs::filesystem_error &e)
            {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
                return "q";
            }
        }
        else
        {
            // User doesn't want to create the directory
            return "q";
        }
    }

    return stemDir;
}

std::vector<std::string> DirectoryCreator::getSubdirectoryNames()
{
    std::vector<std::string> names;
    std::string input;
    int count = 1;

    std::cout << "Enter subdirectory names. Each will be prefixed with a number." << std::endl;
    std::cout << "For example: \"Number Systems\" becomes \"01 - Number Systems\"" << std::endl;

    while (true)
    {
        std::cout << "Enter the name of the next dir inside stem dir (or q to finish): ";
        std::getline(std::cin, input);

        if (input == "q" || input == "Q")
        {
            break;
        }

        // Trim whitespace from input
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

        if (!input.empty())
        {
            names.push_back(input);
            count++;
        }
        else
        {
            std::cout << "Name cannot be empty. Please try again." << std::endl;
        }
    }

    return names;
}

void DirectoryCreator::createSubdirectories(const std::string &stemDir, const std::vector<std::string> &subDirNames)
{
    // Display a summary of directories to be created
    std::cout << "\nCreating " << subDirNames.size() << " directories inside " << stemDir << ":" << std::endl;

    for (size_t i = 0; i < subDirNames.size(); ++i)
    {
        // Format the directory name: "01 - Name", "02 - Name", etc.
        std::string formattedName = std::to_string(i + 1);
        if (formattedName.length() < 2)
        {
            formattedName = "0" + formattedName;
        }
        formattedName += " - " + subDirNames[i];

        // Create the full path
        fs::path fullPath = fs::path(stemDir) / formattedName;

        // Create the directory
        try
        {
            fs::create_directories(fullPath);
            std::cout << "  Created: " << fullPath.filename().string() << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "  Error creating directory: " << e.what() << std::endl;
        }
    }
}
