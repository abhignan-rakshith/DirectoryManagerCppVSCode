#ifndef TEMPLATE_FILES_H
#define TEMPLATE_FILES_H

#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

/**
 * @brief Manages template files embedded in the program
 *
 * TemplateFiles provides access to template files that are embedded in the program
 * as string literals, eliminating the dependency on external files.
 */
class TemplateFiles
{
public:
    /**
     * @brief Structure representing a template file
     */
    struct TemplateFile
    {
        std::string filename;     // Name of the file
        std::string content;      // Content of the file
        std::string subdirectory; // Subdirectory where the file should be placed (empty for root)
    };

    /**
     * @brief Creates all template files in the specified directory
     *
     * @param targetDir Directory where template files should be created
     * @return bool True if all files were created successfully
     */
    static bool createTemplateFilesIn(const fs::path &targetDir);

    /**
     * @brief Gets the number of template files
     *
     * @return int Number of template files
     */
    static int getTemplateFileCount();

    /**
     * @brief Gets a list of all template files
     *
     * @return std::vector<TemplateFile> List of all template files
     */
    static std::vector<TemplateFile> getAllTemplateFiles();

private:
    // Helper method to create a file with the given content
    static bool createFile(const fs::path &filePath, const std::string &content);

    // Helper method to create a directory if it doesn't exist
    static bool createDirectoryIfNeeded(const fs::path &dirPath);

    // Template file contents defined in the implementation file
};

#endif // TEMPLATE_FILES_H