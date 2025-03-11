#ifndef DIRECTORY_CREATOR_H
#define DIRECTORY_CREATOR_H

#include "DirectoryManager.h"
#include <vector>
#include <string>

/**
 * @brief Class for creating directory structures
 *
 * DirectoryCreator handles the creation of directory structures based on user input.
 * It creates a stem directory with numbered subdirectories.
 */
class DirectoryCreator : public DirectoryManager
{
private:
    std::string lastStemDirectory; // Stores the most recently created stem directory path

public:
    /**
     * @brief Constructor initializes the lastStemDirectory
     */
    DirectoryCreator();

    /**
     * @brief Creates a directory structure based on user input
     *
     * Guides the user through creating a stem directory and multiple subdirectories.
     * Each subdirectory is named with a numeric prefix and user-provided name.
     */
    void createDirectoryStructure();

    /**
     * @brief Returns the path of the most recently created stem directory
     *
     * @return std::string The stem directory path or empty if none was created
     */
    std::string getLastStemDirectory() const;

private:
    /**
     * @brief Gets a stem directory path from the user
     *
     * @return std::string The stem directory path or "q" if user wants to quit
     */
    std::string getStemDirectory();

    /**
     * @brief Gets a list of subdirectory names from the user
     *
     * @return std::vector<std::string> List of subdirectory names
     */
    std::vector<std::string> getSubdirectoryNames();

    /**
     * @brief Creates subdirectories inside the stem directory
     *
     * @param stemDir Path to the stem directory
     * @param subDirNames List of subdirectory names
     */
    void createSubdirectories(const std::string &stemDir, const std::vector<std::string> &subDirNames);
};

#endif // DIRECTORY_CREATOR_H