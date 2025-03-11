#include "DirectoryCopier.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

DirectoryCopier::DirectoryCopier()
{
    // Validate that the root directory exists
    if (!isValidDirectory(rootDir))
    {
        std::cerr << "Root directory does not exist: " << rootDir << std::endl;
        throw std::runtime_error("Invalid root directory");
    }
}

void DirectoryCopier::copyFilesToSubdirectories()
{
    std::cout << "\nNice! Let's copy files to subdirectories." << std::endl;

    // Get stem directory
    std::string stemDir = getValidDirectoryPath("Please paste the path to the stem dir: ");
    if (stemDir == "q")
        return;

    copyFilesToSpecificStemDir(stemDir);
}

bool DirectoryCopier::copyFilesToSpecificStemDir(const std::string &stemDir)
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
    std::cout << "\nCopy files from root directory to all subdirectories? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    if (response != "y" && response != "Y")
    {
        std::cout << "Copy operation canceled." << std::endl;
        return false;
    }

    // Copy files to each subdirectory
    for (const auto &subDir : subDirs)
    {
        copyFiles(rootDir, subDir);
    }

    std::cout << "Copy operation completed successfully!" << std::endl;
    return true;
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

void DirectoryCopier::copyFiles(const fs::path &sourceDir, const fs::path &destDir)
{
    std::cout << "Copying to: " << destDir.filename().string() << std::endl;

    try
    {
        // Track progress
        int filesCopied = 0;

        for (const auto &entry : fs::recursive_directory_iterator(sourceDir))
        {
            // Calculate the destination path
            fs::path relativePath = fs::relative(entry.path(), sourceDir);
            fs::path targetPath = destDir / relativePath;

            if (fs::is_directory(entry))
            {
                // Create directory if it doesn't exist
                if (!fs::exists(targetPath))
                {
                    fs::create_directories(targetPath);
                }
            }
            else if (fs::is_regular_file(entry))
            {
                // Create parent directory if needed
                if (!fs::exists(targetPath.parent_path()))
                {
                    fs::create_directories(targetPath.parent_path());
                }

                // Copy the file
                fs::copy_file(entry.path(), targetPath, fs::copy_options::overwrite_existing);
                filesCopied++;
            }
        }

        std::cout << "  Copied " << filesCopied << " files." << std::endl;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error copying files: " << e.what() << std::endl;
    }
}
