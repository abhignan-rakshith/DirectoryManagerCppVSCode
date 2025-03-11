#include "DirectoryCopier.h"
#include "TemplateFiles.h"
#include <iostream>
#include <filesystem>
#include <algorithm> // For std::count_if

namespace fs = std::filesystem;

void DirectoryCopier::copyFilesToSubdirectories()
{
    std::cout << "\nNice! Let's create template files in subdirectories." << std::endl;

    // Get stem directory
    std::string stemDir = getValidDirectoryPath("Please paste the path to the stem dir: ");
    if (stemDir == "q")
        return;

    // Create template files in subdirectories
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
    std::cout << "\nFound " << subDirs.size() << " subdirectories:" << std::endl;
    for (const auto &subDir : subDirs)
    {
        std::cout << "* " << subDir.filename().string() << std::endl;
    }

    // Confirm operation
    std::cout << "\nCreate template files in all subdirectories? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    if (response != "y" && response != "Y")
    {
        std::cout << "Operation canceled." << std::endl;
        return false;
    }

    // Create template files in each subdirectory
    int successCount = 0;
    int totalFiles = TemplateFiles::getTemplateFileCount() * subDirs.size();

    for (const auto &subDir : subDirs)
    {
        std::cout << "Processing: " << subDir.filename().string() << std::endl;
        if (createTemplateFilesIn(subDir))
        {
            successCount++;
        }
    }

    // Report results
    if (successCount == 0)
    {
        std::cout << "Failed to create template files in any directories." << std::endl;
        return false;
    }
    else if (successCount < subDirs.size())
    {
        std::cout << "Template files created in " << successCount << " of " << subDirs.size()
                  << " directories. Check error messages above." << std::endl;
    }
    else
    {
        std::cout << "Template files successfully created in all " << successCount << " directories." << std::endl;
    }

    return successCount > 0;
}

std::vector<fs::path> DirectoryCopier::getAllSubdirectories(const std::string &stemDir)
{
    std::vector<fs::path> subDirs;

    try
    {
        // Check if directory exists first
        if (!fs::exists(stemDir))
        {
            std::cerr << "Error: Directory does not exist: " << stemDir << std::endl;
            return subDirs;
        }

        // Iterate through directory entries
        for (const auto &entry : fs::directory_iterator(stemDir))
        {
            // Only include directories (not files)
            if (fs::is_directory(entry))
            {
                // Skip hidden directories (starting with dot)
                std::string filename = entry.path().filename().string();
                if (!filename.empty() && filename[0] != '.')
                {
                    subDirs.push_back(entry.path());
                }
            }
        }

        // Sort directories by name for consistent results
        std::sort(subDirs.begin(), subDirs.end());
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
        // Create template files in destination directory
        bool success = TemplateFiles::createTemplateFilesIn(destDir);

        // Report status
        if (success)
        {
            std::cout << "  Created " << TemplateFiles::getTemplateFileCount()
                      << " template files successfully." << std::endl;
        }
        else
        {
            std::cout << "  Some template files could not be created." << std::endl;
        }

        return success;
    }
    catch (const std::exception &e)
    {
        std::cerr << "  Error creating template files: " << e.what() << std::endl;
        return false;
    }
}
