#include "TemplateFiles.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Define the template file contents as string literals
const std::string TemplateFiles::MAIN_CPP = R"(#include <iostream>

consteval int get_value()
{
    return 3;
}

int main()
{
    constexpr int value = get_value();
    std::cout << "value : " << value << std::endl;
    return 0;
})";

const std::string TemplateFiles::CPP_PROPERTIES_JSON = R"({
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
})";

const std::string TemplateFiles::TASKS_JSON = R"({
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
})";

bool TemplateFiles::createTemplateFilesIn(const fs::path &targetDir)
{
    try
    {
        // Ensure the target directory exists
        if (!createDirectoryIfNeeded(targetDir))
        {
            return false;
        }

        // Create main.cpp in the target directory
        if (!createFile(targetDir / "main.cpp", MAIN_CPP))
        {
            return false;
        }

        // Create .vscode directory
        fs::path vscodeDir = targetDir / ".vscode";
        if (!createDirectoryIfNeeded(vscodeDir))
        {
            return false;
        }

        // Create configuration files in .vscode directory
        if (!createFile(vscodeDir / "c_cpp_properties.json", CPP_PROPERTIES_JSON))
        {
            return false;
        }

        if (!createFile(vscodeDir / "tasks.json", TASKS_JSON))
        {
            return false;
        }

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error creating template files: " << e.what() << std::endl;
        return false;
    }
}

int TemplateFiles::getTemplateFileCount()
{
    // Currently we have 3 template files
    return 3;
}

bool TemplateFiles::createFile(const fs::path &filePath, const std::string &content)
{
    try
    {
        std::ofstream file(filePath, std::ios::out);
        if (!file)
        {
            std::cerr << "Error: Could not create file: " << filePath << std::endl;
            return false;
        }

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
