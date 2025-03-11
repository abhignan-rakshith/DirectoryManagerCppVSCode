#include "TemplateFiles.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Get all template files with their content and location
std::vector<TemplateFiles::TemplateFile> TemplateFiles::getAllTemplateFiles()
{
    // Define all template files in a vector for easier maintenance
    std::vector<TemplateFile> files = {
        // Main.cpp in root directory
        {
            "main.cpp",
            R"(#include <iostream>

consteval int get_value()
{
    return 3;
}

int main()
{
    constexpr int value = get_value();
    std::cout << "value : " << value << std::endl;
    return 0;
})",
            "" // Empty subdirectory means root
        },

        // c_cpp_properties.json in .vscode subdirectory
        {
            "c_cpp_properties.json",
            R"({
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.19041.0",
            "compilerPath": "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x64/cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "windows-msvc-x64"
        }
    ],
    "version": 4
})",
            ".vscode"},

        // tasks.json in .vscode subdirectory
        {
            "tasks.json",
            R"({
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "Build GCC Compiler",
			"command": "C:\\mingw64\\bin\\g++.exe",
			"args": [
				"-g",
				"-std=c++20",
				"${workspaceFolder}\\*.cpp",
				"-o",
				"${fileDirname}\\rooster.exe"
			],
			"options": {
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": "build",
			"detail": "compiler: C:\\mingw64\\bin\\g++.exe"
		},
		{
			"type": "cppbuild",
			"label": "Build with MSVC Compiler",
			"command": "cl.exe",
			"args": [
				"/Zi",
				"/std:c++latest",
				"/EHsc",
				"/Fe:",
				"${fileDirname}\\rooster.exe",
				"${workspaceFolder}\\*.cpp"
			],
			"options": {
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$msCompile"
			],
			"group": "build",
			"detail": "compiler: cl.exe"
		},
		{
			"type": "cppbuild",
			"label": "Build with Clang Compiler",
			"command": "C:\\mingw64\\bin\\clang++.exe",
			"args": [
				"-g",
				"-std=c++20",
				"${workspaceFolder}\\*.cpp",
				"-o",
				"${fileDirname}\\rooster.exe"
			],
			"options": {
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": "build",
			"detail": "compiler: C:\\mingw64\\bin\\clang++.exe"
		}
	]
})",
            ".vscode"}};

    return files;
}

bool TemplateFiles::createTemplateFilesIn(const fs::path &targetDir)
{
    try
    {
        // Get all template files
        std::vector<TemplateFile> files = getAllTemplateFiles();

        // Ensure the target directory exists
        if (!createDirectoryIfNeeded(targetDir))
        {
            return false;
        }

        // Create all template files
        bool allSuccessful = true;
        for (const auto &file : files)
        {
            // Determine the full path for the file
            fs::path filePath;
            if (file.subdirectory.empty())
            {
                // File goes in the root directory
                filePath = targetDir / file.filename;
            }
            else
            {
                // File goes in a subdirectory
                fs::path subDir = targetDir / file.subdirectory;
                if (!createDirectoryIfNeeded(subDir))
                {
                    allSuccessful = false;
                    continue;
                }
                filePath = subDir / file.filename;
            }

            // Create the file
            if (!createFile(filePath, file.content))
            {
                allSuccessful = false;
            }
        }

        return allSuccessful;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating template files: " << e.what() << std::endl;
        return false;
    }
}

int TemplateFiles::getTemplateFileCount()
{
    return getAllTemplateFiles().size();
}

bool TemplateFiles::createFile(const fs::path &filePath, const std::string &content)
{
    try
    {
        // Open file for writing
        std::ofstream file(filePath, std::ios::out);
        if (!file)
        {
            std::cerr << "Error: Could not create file: " << filePath << std::endl;
            return false;
        }

        // Write content to file
        file << content;
        file.close();

        std::cout << "Created file: " << filePath.filename().string() << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error writing file: " << e.what() << std::endl;
        return false;
    }
}

bool TemplateFiles::createDirectoryIfNeeded(const fs::path &dirPath)
{
    try
    {
        // Create directory if it doesn't exist
        if (!fs::exists(dirPath))
        {
            if (!fs::create_directories(dirPath))
            {
                std::cerr << "Error: Could not create directory: " << dirPath << std::endl;
                return false;
            }
            std::cout << "Created directory: " << dirPath.string() << std::endl;
        }
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return false;
    }
}
