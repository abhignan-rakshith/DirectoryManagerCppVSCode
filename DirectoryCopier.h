#ifndef DIRECTORY_COPIER_H
#define DIRECTORY_COPIER_H

#include "DirectoryManager.h"
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Class for creating template files in directories
 *
 * DirectoryCopier handles the creation of template files in user-specified directories.
 * Instead of copying from a root directory, it creates files using embedded templates.
 */
class DirectoryCopier : public DirectoryManager
{
public:
    /**
     * @brief Constructor
     */
    DirectoryCopier() = default;

    /**
     * @brief Creates template files in subdirectories specified by user
     *
     * Takes a stem directory from user input, locates all subdirectories,
     * and creates template files in each subdirectory.
     */
    void copyFilesToSubdirectories();

    /**
     * @brief Creates template files in a specific stem directory's subdirectories
     *
     * @param stemDir Path to the stem directory containing subdirectories
     * @return bool True if template files were created successfully in at least one subdirectory
     */
    bool copyTemplateFilesToSpecificStemDir(const std::string &stemDir);

private:
    /**
     * @brief Gets all subdirectories in a directory
     *
     * @param stemDir Path to the directory to scan
     * @return std::vector<fs::path> List of subdirectory paths
     */
    std::vector<fs::path> getAllSubdirectories(const std::string &stemDir);

    /**
     * @brief Creates template files in a directory
     *
     * @param destDir Directory where template files should be created
     * @return bool True if all files were created successfully
     */
    bool createTemplateFilesIn(const fs::path &destDir);
};

#endif // DIRECTORY_COPIER_H