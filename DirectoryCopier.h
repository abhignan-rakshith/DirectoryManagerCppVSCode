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
private:
    const std::string rootDir = "F:\\Dev\\My_Cpp-20\\Template_Win_Work";

public:
    DirectoryCopier();
    void copyFilesToSubdirectories();

private:
    std::vector<fs::path> getAllSubdirectories(const std::string &stemDir);
    void copyFiles(const fs::path &sourceDir, const fs::path &destDir);
};

#endif // DIRECTORY_COPIER_H