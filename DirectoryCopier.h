#ifndef DIRECTORY_COPIER_H
#define DIRECTORY_COPIER_H

#include "DirectoryManager.h"
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Class for copying files to directories
class DirectoryCopier : public DirectoryManager
{
public:
    DirectoryCopier();
    void copyFilesToSubdirectories();

    // Method to copy template files to a specific stem directory
    bool copyTemplateFilesToSpecificStemDir(const std::string &stemDir);

private:
    std::vector<fs::path> getAllSubdirectories(const std::string &stemDir);

    // Method to copy template files to a destination directory
    bool createTemplateFilesIn(const fs::path &destDir);
};

#endif // DIRECTORY_COPIER_H