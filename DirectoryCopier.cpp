#include "DirectoryCopier.h"
#include "TemplateFiles.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

DirectoryCopier::DirectoryCopier()
{
    // No need to validate root directory anymore as we're using embedded templates
}

void DirectoryCopier::copyFilesToSubdirectories()
{
    std::cout << "\nNice! Let's copy template files to subdirectories." << std::endl;

    // Get stem directory
    std::string stemDir = getValidDirectoryPath("Please paste the path to the stem dir: ");
    if (stemDir == "q")
        return;

    copyTemplateFilesToSpecificStemDir(stemDir);
}

bool DirectoryCopier::copyTemplateFilesToSpecificStemDir(const std::string &stemDir)
{
    // Get all subdirectories
    std::vector<fs::path> subDirs = getAllSubdirectories(stemDir);
    if (subDirs.empty())
    {
        std::cout << "No subdirectories found in the stem directory." << std::endl;
        return false;
    }

    // Display subdirectories
    std::cout << "\nFound the following subdirectories:" << std::endl;
    for (const auto &subDir : subDirs)
    {
        std::cout << "* " << subDir.filename().string() << std::endl;
    }

    // Confirm copy operation
    std::cout << "\nCreate template files in all subdirectories? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    if (response != "y" && response != "Y")
    {
        std::cout << "Operation canceled." << std::endl;
        return false;
    }

    // Copy template files to each subdirectory
    int successCount = 0;
    for (const auto &subDir : subDirs)
    {
        std::cout << "Processing: " << subDir.filename().string() << std::endl;
        if (createTemplateFilesIn(subDir))
        {
            successCount++;
        }
    }

    std::cout << "Template files created in " << successCount << " of " << subDirs.size() << " directories." << std::endl;
    return successCount > 0;
}

std::vector<fs::path> DirectoryCopier::getAllSubdirectories(const std::string &stemDir)
{
    std::vector<fs::path> subDirs;

    try
    {
        for (const auto &entry : fs::directory_iterator(stemDir))
        {
            if (fs::is_directory(entry))
            {
                subDirs.push_back(entry.path());
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }

    return subDirs;
}

bool DirectoryCopier::createTemplateFilesIn(const fs::path &destDir)
{
    try
    {
        bool success = TemplateFiles::createTemplateFilesIn(destDir);
        if (success)
        {
            std::cout << "  Created " << TemplateFiles::getTemplateFileCount() << " template files." << std::endl;
        }
        return success;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating template files: " << e.what() << std::endl;
        return false;
    }
}
