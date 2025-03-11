#include "DirectoryManager.h"
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string DirectoryManager::cleanPath(const std::string &path) const
{
    if (path.length() >= 2 && (path.front() == '"' && path.back() == '"'))
    {
        return path.substr(1, path.length() - 2);
    }
    return path;
}

bool DirectoryManager::isValidDirectory(const std::string &path) const
{
    std::string cleanedPath = cleanPath(path);
    try
    {
        return fs::exists(cleanedPath) && fs::is_directory(cleanedPath);
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error validating directory: " << e.what() << std::endl;
        return false;
    }
}

std::string DirectoryManager::getValidDirectoryPath(const std::string &prompt) const
{
    std::string path;
    bool isValid = false;

    while (!isValid)
    {
        std::cout << prompt;
        std::getline(std::cin, path);

        // Check for quit command
        if (path == "q" || path == "Q")
        {
            return "q";
        }

        path = cleanPath(path);

        if (isValidDirectory(path))
        {
            isValid = true;
        }
        else
        {
            std::cout << "Invalid directory path. Please try again." << std::endl;
        }
    }

    return path;
}
