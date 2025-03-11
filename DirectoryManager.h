#ifndef DIRECTORY_MANAGER_H
#define DIRECTORY_MANAGER_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Base class for directory operations
class DirectoryManager
{
protected:
    // Utility function to clean paths with quotation marks
    std::string cleanPath(const std::string &path) const;

    // Validate if a path is a valid directory
    bool isValidDirectory(const std::string &path) const;

    // Get a valid directory path from user
    std::string getValidDirectoryPath(const std::string &prompt) const;
};

#endif // DIRECTORY_MANAGER_H