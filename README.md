# Directory Template Tool

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg)
![Version](https://img.shields.io/badge/version-6.0-green.svg)

A powerful command-line tool for creating directory structures with embedded template files for C++ development projects. Simplifies the setup of new programming projects by automating repetitive directory creation and template file generation.

## ✨ Features

- **Directory Structure Creation**: Easily create numbered directory structures (e.g., "01 - Number Systems", "02 - Integer Modifiers")
- **Markdown Import**: Import directory structures from markdown files, saving time on manual entry
- **Template File Generation**: Create standard C++20 template files with embedded VS Code configurations
- **Self-Contained Design**: All template files are embedded within the program, eliminating external dependencies
- **Flexible Usage**: Create directories first, then add template files, or add template files to existing directories
- **VS Code Integration**: Automatically creates proper `.vscode` configuration for C++20 development
- **Name Sanitization**: Automatically sanitizes directory names to ensure file system compatibility

## 📋 Table of Contents

- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Markdown Structure Format](#-markdown-structure-format)
- [Template Files](#-template-files)
- [Build Instructions](#-build-instructions)
- [Project Structure](#-project-structure)
- [Contributing](#-contributing)

## 📌 Requirements

- C++17 or higher compiler (C++20 recommended)
- Filesystem support
- Windows, Linux, or macOS

## 🚀 Installation

### Compile from Source

```bash
# Clone the repository
git clone https://github.com/abhignan-rakshith/DirectoryManagerCppVSCode.git
cd <into the dir>

# Compile with optimizations
g++ -std=c++20 -Os main.cpp DirectoryManager.cpp DirectoryCreator.cpp DirectoryCopier.cpp UserInterface.cpp TemplateFiles.cpp -o directory_template_tool

# On older Linux systems, you may need to add -lstdc++fs:
# g++ -std=c++20 -Os main.cpp DirectoryManager.cpp DirectoryCreator.cpp DirectoryCopier.cpp UserInterface.cpp TemplateFiles.cpp -o directory_template_tool -lstdc++fs
```

## 🔍 Usage

Run the program and follow the interactive prompts:

```bash
./directory_template_tool
```

### Main Menu

```
====================================
Welcome to Directory Template Tool!
====================================
What do you want to do today?

Choose from below:
  1. Create folder structure
  2. Create template files in existing directories

Enter your choice (1-2):
```

### Option 1: Create Folder Structure

#### Manual Entry Method
1. Enter the path to the main stem directory
2. Choose 'n' when asked if you want to use a markdown file
3. Enter names for subdirectories (e.g., "Number Systems", "Integer Modifiers")
4. Enter 'q' when done adding directories
5. The program will create directories with numbered prefixes (e.g., "01 - Number Systems")
6. Choose whether to add template files to these directories

#### Markdown Import Method (New in v6)
1. Choose 'y' when asked if you want to use a markdown file
2. Enter the path to your markdown file containing the directory structure
3. Review the parsed structure and make any corrections if needed
4. Enter the parent directory where the stem directory should be created
5. The program will create the entire directory structure automatically
6. Choose whether to add template files to these directories

### Option 2: Create Template Files in Existing Directories

1. Enter the path to a stem directory containing subdirectories
2. The program will list all subdirectories found
3. Confirm to create template files in all subdirectories
4. Template files will be generated in each subdirectory

## 📝 Markdown Structure Format

When creating directory structures from markdown files (new in v6), your markdown file should follow this format:

```markdown
Stem Directory Name
|- Subdirectory 1
|- Subdirectory 2
|- Subdirectory 3
```

Example for a web development course:

```markdown
Web Development Course
|- HTML Basics
|- CSS Fundamentals
|- JavaScript Essentials
|- DOM Manipulation
|- Responsive Design
```

The program also supports alternative markdown list formats:

```markdown
Web Development Course
- HTML Basics
- CSS Fundamentals

# OR

Web Development Course
* HTML Basics
* CSS Fundamentals
```

The first line is used as the stem directory name, and each list item becomes a subdirectory with a numbered prefix.

## 📁 Template Files

The program generates the following template files:

1. **main.cpp** - A simple C++20 template using `consteval` feature:
   ```cpp
   #include <iostream>

   consteval int get_value()
   {
       return 3;
   }

   int main()
   {
       constexpr int value = get_value();
       std::cout << "value : " << value << std::endl;
       return 0;
   }
   ```

2. **.vscode/c_cpp_properties.json** - VS Code C++ configuration for C++20
3. **.vscode/tasks.json** - VS Code build tasks for GCC, MSVC, and Clang compilers

## 🔨 Build Instructions

### Using g++

For the smallest binary size with optimizations:

```bash
g++ -std=c++20 -Os main.cpp DirectoryManager.cpp DirectoryCreator.cpp DirectoryCopier.cpp UserInterface.cpp TemplateFiles.cpp -o directory_template_tool
```

For debugging:

```bash
g++ -std=c++20 -g main.cpp DirectoryManager.cpp DirectoryCreator.cpp DirectoryCopier.cpp UserInterface.cpp TemplateFiles.cpp -o directory_template_tool
```

## 📂 Project Structure

```
directory-template-tool/

├── main.cpp                 # Entry point
├── DirectoryManager.h       # Base class for directory operations
├── DirectoryManager.cpp
├── DirectoryCreator.h       # Creates directory structures
├── DirectoryCreator.cpp
├── DirectoryCopier.h        # Creates template files
├── DirectoryCopier.cpp
├── TemplateFiles.h          # Manages embedded template files
├── TemplateFiles.cpp
├── UserInterface.h          # Handles user interaction
|── UserInterface.cpp
└── README.md
```

## 🤝 Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Commit your changes: `git commit -am 'Add my feature'`
4. Push to the branch: `git push origin feature/my-feature`
5. Submit a pull request