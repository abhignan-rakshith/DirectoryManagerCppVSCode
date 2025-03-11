#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Function to remove quotation marks from a path
std::string cleanPath(const std::string& path) {
    if (path.length() >= 2 && 
        (path.front() == '"' && path.back() == '"')) {
        // Remove the first and last characters (the quotes)
        return path.substr(1, path.length() - 2);
    }
    return path;
}

// Function to copy files from source to destination
void copyFiles(const fs::path& sourceDir, const fs::path& destDir) {
    // Create destination directory if it doesn't exist
    if (!fs::exists(destDir)) {
        try {
            fs::create_directories(destDir);
            std::cout << "Created directory: " << destDir << std::endl;
        } catch (fs::filesystem_error& e) {
            std::cerr << "Error creating directory: " << e.what() << std::endl;
            return;
        }
    }

    // Copy all files and subdirectories
    try {
        for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
            // Calculate the destination path
            fs::path targetPath = destDir / fs::relative(entry.path(), sourceDir);
            
            if (fs::is_directory(entry)) {
                // Create directory if it doesn't exist
                if (!fs::exists(targetPath)) {
                    fs::create_directories(targetPath);
                }
            } else if (fs::is_regular_file(entry)) {
                // Create parent directory if needed
                if (!fs::exists(targetPath.parent_path())) {
                    fs::create_directories(targetPath.parent_path());
                }
                // Copy the file
                fs::copy_file(entry.path(), targetPath, fs::copy_options::overwrite_existing);
            }
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error copying files: " << e.what() << std::endl;
    }
}

int main() {
    // Root directory (source)
    std::string rootDir = "F:\\Dev\\My_Cpp-20\\Template_Win_Work";
    rootDir = cleanPath(rootDir); // Clean the root path if it has quotes
    
    // Check if source directory exists
    if (!fs::exists(rootDir)) {
        std::cerr << "Source directory does not exist: " << rootDir << std::endl;
        return 1;
    }
    
    // Vector to store destination directories
    std::vector<std::string> destDirs;
    
    // Welcome message
    std::cout << "Welcome Player!" << std::endl;
    
    // Get destination directories from user
    std::string input;
    int dirCount = 1;
    
    while (true) {
        std::cout << "Paste the path to dir " << dirCount << " or enter q: " << std::endl;
        
        std::getline(std::cin, input);
        
        // Check if user wants to quit
        if (input == "q" || input == "Q") {
            break;
        }
        
        // Clean the path (remove quotes if present)
        input = cleanPath(input);
        
        // Add the directory to the list
        destDirs.push_back(input);
        dirCount++;
    }
    
    // Check if at least one destination was provided
    if (destDirs.empty()) {
        std::cout << "No destination directories provided. Nothing to do." << std::endl;
        std::cout << "Bye!" << std::endl;
        return 0;
    }
    
    // Copy files to each destination directory
    for (const auto& destDir : destDirs) {
        copyFiles(rootDir, destDir);
    }
    
    // Success message
    std::cout << "The files and folders have been copied to destination dir!" << std::endl;
    std::cout << "Bye!" << std::endl;
    
    return 0;
}
