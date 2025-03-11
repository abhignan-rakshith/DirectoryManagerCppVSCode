#include "DirectoryCreator.h"
#include <iostream>
#include <filesystem>
#include <iomanip>   // For formatted output
#include <fstream>   // For file operations
#include <algorithm> // For std::replace

namespace fs = std::filesystem;

DirectoryCreator::DirectoryCreator() : lastStemDirectory("")
{
    // Initialize with empty string
}

void DirectoryCreator::createDirectoryStructure()
{
    std::cout << "\nCool!, let's create the dir tree!" << std::endl;

    // Ask if user wants to use markdown file first
    std::cout << "Do you want to use a markdown file for directory structure? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    std::string stemDir;
    std::vector<std::string> subDirNames;

    if (response == "y" || response == "Y")
    {
        // Get directory structure from markdown
        std::string stemDirName;
        std::tie(stemDirName, subDirNames) = getDirectoryStructureFromMarkdown();

        if (subDirNames.empty())
        {
            std::cout << "No valid subdirectories found in markdown file." << std::endl;
            return;
        }

        // Now get the parent directory where the stem directory should be created
        std::cout << "Enter the parent directory where '" << stemDirName << "' should be created: ";
        std::string parentDir;
        std::getline(std::cin, parentDir);

        // Clean path
        parentDir = cleanPath(parentDir);

        // Validate parent directory
        if (!isValidDirectory(parentDir))
        {
            std::cout << "Invalid parent directory. Create it? (y/n): ";
            std::string createResponse;
            std::getline(std::cin, createResponse);

            if (createResponse == "y" || createResponse == "Y")
            {
                try
                {
                    fs::create_directories(parentDir);
                    std::cout << "Created directory: " << parentDir << std::endl;
                }
                catch (const fs::filesystem_error &e)
                {
                    std::cerr << "Error creating directory: " << e.what() << std::endl;
                    return;
                }
            }
            else
            {
                std::cout << "Operation canceled." << std::endl;
                return;
            }
        }

        // Create full stem directory path
        stemDir = (fs::path(parentDir) / stemDirName).string();

        // Create stem directory if it doesn't exist
        if (!fs::exists(stemDir))
        {
            try
            {
                fs::create_directories(stemDir);
                std::cout << "Created stem directory: " << stemDir << std::endl;
            }
            catch (const fs::filesystem_error &e)
            {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
                return;
            }
        }
    }
    else
    {
        // Get stem directory the traditional way
        stemDir = getStemDirectory();
        if (stemDir == "q")
            return; // User wants to quit

        // Use existing method to get subdirectory names
        subDirNames = getSubdirectoryNames();
    }

    // Store the stem directory for later reference
    lastStemDirectory = stemDir;

    if (subDirNames.empty())
    {
        std::cout << "No directories to create." << std::endl;
        return;
    }

    // Create the directories
    createSubdirectories(stemDir, subDirNames);

    std::cout << "Directory structure created successfully!" << std::endl;
}

std::string DirectoryCreator::getLastStemDirectory() const
{
    return lastStemDirectory;
}

std::string DirectoryCreator::getStemDirectory()
{
    // First try to get existing directory
    std::string stemDir = getValidDirectoryPath("First paste the path to the main stem dir: ");

    // If user entered 'q', return
    if (stemDir == "q")
        return "q";

    // If directory doesn't exist, ask if they want to create it
    if (!isValidDirectory(stemDir))
    {
        std::cout << "Directory doesn't exist. Create it? (y/n): ";
        std::string response;
        std::getline(std::cin, response);

        if (response == "y" || response == "Y")
        {
            try
            {
                fs::create_directories(stemDir);
                std::cout << "Created directory: " << stemDir << std::endl;
            }
            catch (const fs::filesystem_error &e)
            {
                std::cerr << "Error creating directory: " << e.what() << std::endl;
                return "q";
            }
        }
        else
        {
            // User doesn't want to create the directory
            return "q";
        }
    }

    return stemDir;
}

std::vector<std::string> DirectoryCreator::getSubdirectoryNames()
{
    std::vector<std::string> names;
    std::string input;
    int count = 1;

    std::cout << "Enter subdirectory names. Each will be prefixed with a number." << std::endl;
    std::cout << "For example: \"Number Systems\" becomes \"01 - Number Systems\"" << std::endl;

    while (true)
    {
        std::cout << "Enter the name of the next dir inside stem dir (or q to finish): ";
        std::getline(std::cin, input);

        if (input == "q" || input == "Q")
        {
            break;
        }

        // Trim whitespace from input
        if (!input.empty())
        {
            size_t first = input.find_first_not_of(" \t\n\r\f\v");
            if (first != std::string::npos)
            {
                size_t last = input.find_last_not_of(" \t\n\r\f\v");
                input = input.substr(first, (last - first + 1));
            }
            else
            {
                input = "";
            }
        }

        if (!input.empty())
        {
            names.push_back(input);
            count++;
        }
        else
        {
            std::cout << "Name cannot be empty. Please try again." << std::endl;
        }
    }

    // Show entered names and allow editing
    if (!names.empty())
    {
        std::cout << "\nEntered directory names:" << std::endl;
        for (size_t i = 0; i < names.size(); ++i)
        {
            std::cout << (i + 1) << ". " << names[i] << std::endl;
        }

        std::cout << "\nDo you want to modify any names? (y/n): ";
        std::string response;
        std::getline(std::cin, response);

        if (response == "y" || response == "Y")
        {
            while (true)
            {
                std::cout << "Enter index to edit (1-" << names.size() << ") or 0 to finish: ";
                std::getline(std::cin, input);

                try
                {
                    int index = std::stoi(input);
                    if (index == 0)
                        break;

                    if (index >= 1 && index <= static_cast<int>(names.size()))
                    {
                        std::cout << "Current name: " << names[index - 1] << std::endl;
                        std::cout << "Enter new name: ";
                        std::getline(std::cin, input);

                        if (!input.empty())
                        {
                            names[index - 1] = input;
                            std::cout << "Name updated." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Invalid index." << std::endl;
                    }
                }
                catch (...)
                {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                }
            }
        }
    }

    return names;
}

void DirectoryCreator::createSubdirectories(const std::string &stemDir, const std::vector<std::string> &subDirNames)
{
    // Display a summary of directories to be created
    std::cout << "\nCreating " << subDirNames.size() << " directories inside " << stemDir << ":" << std::endl;

    for (size_t i = 0; i < subDirNames.size(); ++i)
    {
        // Sanitize the directory name
        std::string sanitizedName = slugifyDirectoryName(subDirNames[i]);

        // Format the directory name: "01 - Name", "02 - Name", etc.
        std::string formattedName = std::to_string(i + 1);
        if (formattedName.length() < 2)
        {
            formattedName = "0" + formattedName;
        }
        formattedName += " - " + sanitizedName;

        // Create the full path
        fs::path fullPath = fs::path(stemDir) / formattedName;

        // Create the directory
        try
        {
            fs::create_directories(fullPath);
            std::cout << "  Created: " << fullPath.filename().string() << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "  Error creating directory: " << e.what() << std::endl;
        }
    }
}

std::pair<std::string, std::vector<std::string>> DirectoryCreator::getDirectoryStructureFromMarkdown()
{
    std::string markdownPath;
    std::vector<std::string> subDirNames;
    std::string stemDirName;

    std::cout << "Enter path to markdown file with directory structure: ";
    std::getline(std::cin, markdownPath);

    // Clean path (reuse existing cleanPath method)
    markdownPath = cleanPath(markdownPath);

    try
    {
        // Check if file exists
        if (!fs::exists(markdownPath))
        {
            std::cerr << "Error: File does not exist: " << markdownPath << std::endl;
            return {"", {}};
        }

        // Read markdown file
        std::ifstream markdownFile(markdownPath);
        if (!markdownFile)
        {
            std::cerr << "Error: Could not open file: " << markdownPath << std::endl;
            return {"", {}};
        }

        // Parse the file
        std::string line;
        bool firstLine = true;

        while (std::getline(markdownFile, line))
        {
            // Trim whitespace
            if (!line.empty())
            {
                size_t first = line.find_first_not_of(" \t\n\r\f\v");
                if (first != std::string::npos)
                {
                    size_t last = line.find_last_not_of(" \t\n\r\f\v");
                    line = line.substr(first, (last - first + 1));
                }
                else
                {
                    line = "";
                }
            }

            // Skip empty lines
            if (line.empty())
                continue;

            // First non-empty line is considered the stem directory name
            if (firstLine)
            {
                // Remove any markdown heading syntax (# ) if present
                if (line.find("# ") == 0)
                    stemDirName = line.substr(2);
                else
                    stemDirName = line;

                firstLine = false;
                continue;
            }

            // Check if line represents a subdirectory (starts with |- or - or * or similar markdown list indicators)
            if (line.find("|-") == 0 || line.find("- ") == 0 || line.find("* ") == 0)
            {
                // Extract directory name by removing the marker and trimming
                size_t nameStart = line.find_first_not_of("|- *");
                if (nameStart != std::string::npos)
                {
                    std::string dirName = line.substr(nameStart);
                    if (!dirName.empty())
                    {
                        size_t first = dirName.find_first_not_of(" \t");
                        if (first != std::string::npos)
                        {
                            dirName = dirName.substr(first);
                        }
                    }
                    if (!dirName.empty())
                    {
                        subDirNames.push_back(dirName);
                    }
                }
            }
        }

        // Display parsed structure and allow editing
        std::cout << "\nParsed directory structure:" << std::endl;
        std::cout << "Stem directory: " << stemDirName << std::endl;
        std::cout << "Subdirectories:" << std::endl;
        for (const auto &dir : subDirNames)
        {
            std::cout << "|- " << dir << std::endl;
        }

        // Allow editing of parsed data
        std::cout << "\nDo you wish to modify any of the parsed names? (y/n): ";
        std::string response;
        std::getline(std::cin, response);

        if (response == "y" || response == "Y")
        {
            std::string input;

            // Edit stem directory name
            std::cout << "Enter stem dir correction or press Enter to skip: ";
            std::getline(std::cin, input);
            if (!input.empty())
            {
                stemDirName = input;
            }

            // Edit subdirectory names
            for (size_t i = 0; i < subDirNames.size(); ++i)
            {
                std::cout << "Enter correction for '" << subDirNames[i] << "' or press Enter to skip: ";
                std::getline(std::cin, input);
                if (!input.empty())
                {
                    subDirNames[i] = input;
                }
            }

            // Allow adding new subdirectories
            std::cout << "Add more subdirectories? (y/n): ";
            std::getline(std::cin, response);
            if (response == "y" || response == "Y")
            {
                while (true)
                {
                    std::cout << "Enter new subdirectory name (or q to finish): ";
                    std::getline(std::cin, input);

                    if (input == "q" || input == "Q")
                        break;

                    if (!input.empty())
                    {
                        subDirNames.push_back(input);
                    }
                }
            }
        }

        return {stemDirName, subDirNames};
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing markdown file: " << e.what() << std::endl;
        return {"", {}};
    }
}

std::vector<std::string> DirectoryCreator::parseMarkdownFile(const std::string &markdownPath)
{
    std::vector<std::string> subDirNames;

    try
    {
        std::ifstream markdownFile(markdownPath);
        if (!markdownFile)
        {
            std::cerr << "Error: Could not open file: " << markdownPath << std::endl;
            return {};
        }

        std::string line;
        bool firstLine = true;

        while (std::getline(markdownFile, line))
        {
            // Skip first line (assumed to be stem directory)
            if (firstLine)
            {
                firstLine = false;
                continue;
            }

            // Trim whitespace
            if (!line.empty())
            {
                size_t first = line.find_first_not_of(" \t\n\r\f\v");
                if (first != std::string::npos)
                {
                    size_t last = line.find_last_not_of(" \t\n\r\f\v");
                    line = line.substr(first, (last - first + 1));
                }
                else
                {
                    line = "";
                }
            }

            // Skip empty lines
            if (line.empty())
                continue;

            // Check if line represents a subdirectory
            if (line.find("|-") == 0 || line.find("- ") == 0 || line.find("* ") == 0)
            {
                // Extract directory name
                size_t nameStart = line.find_first_not_of("|- *");
                if (nameStart != std::string::npos)
                {
                    std::string dirName = line.substr(nameStart);
                    if (!dirName.empty())
                    {
                        size_t first = dirName.find_first_not_of(" \t");
                        if (first != std::string::npos)
                        {
                            dirName = dirName.substr(first);
                        }
                    }
                    if (!dirName.empty())
                    {
                        subDirNames.push_back(dirName);
                    }
                }
            }
        }

        return subDirNames;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing markdown file: " << e.what() << std::endl;
        return {};
    }
}

std::string DirectoryCreator::slugifyDirectoryName(const std::string &dirName)
{
    std::string result = dirName;

    // Define invalid characters for Windows file systems
    const std::string invalidChars = "<>:\"/\\|?*";

    // Replace invalid characters with underscores
    for (char c : invalidChars)
    {
        std::replace(result.begin(), result.end(), c, '_');
    }

    // Check for reserved names (Windows specific)
    std::vector<std::string> reservedNames = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};

    // If the name is reserved, append an underscore
    for (const auto &reserved : reservedNames)
    {
        if (result == reserved)
        {
            result += "_";
            break;
        }
    }

    return result;
}