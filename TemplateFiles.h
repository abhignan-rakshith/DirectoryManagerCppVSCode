#ifndef TEMPLATE_FILES_H
#define TEMPLATE_FILES_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Class for managing template files embedded in the program
class TemplateFiles
{
public:
    // Creates all template files in the specified directory
    static bool createTemplateFilesIn(const fs::path &targetDir);

    // Gets the number of files that would be created
    static int getTemplateFileCount();

private:
    // Template file contents as string literals
    static const std::string MAIN_CPP;
    static const std::string CPP_PROPERTIES_JSON;
    static const std::string TASKS_JSON;

    // Helper method to create a file with the given content
    static bool createFile(const fs::path &filePath, const std::string &content);

    // Helper method to create a directory if it doesn't exist
    static bool createDirectoryIfNeeded(const fs::path &dirPath);
};

#endif // TEMPLATE_FILES_H
