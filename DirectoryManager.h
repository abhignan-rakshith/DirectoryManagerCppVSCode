#ifndef DIRECTORY_MANAGER_H
#define DIRECTORY_MANAGER_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Base class for directory operations
 *
 * DirectoryManager serves as a base class providing common functionality
 * for directory manipulation and validation throughout the application.
 */
class DirectoryManager
{
protected:
    /**
     * @brief Removes quotation marks from paths if present
     *
     * @param path The path string that might contain quotation marks
     * @return std::string The cleaned path without quotation marks
     */
    std::string cleanPath(const std::string &path) const;

    /**
     * @brief Checks if a path is a valid directory
     *
     * @param path The path to validate
     * @return bool True if the path exists and is a directory
     */
    bool isValidDirectory(const std::string &path) const;

    /**
     * @brief Gets a valid directory path from user with validation
     *
     * @param prompt The message to display to the user
     * @return std::string The validated directory path or "q" if user wants to quit
     */
    std::string getValidDirectoryPath(const std::string &prompt) const;
};

#endif // DIRECTORY_MANAGER_H