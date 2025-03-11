#ifndef DIRECTORY_CREATOR_H
#define DIRECTORY_CREATOR_H

#include "DirectoryManager.h"
#include <vector>
#include <string>

// Class for creating directory structure
class DirectoryCreator : public DirectoryManager
{
public:
    void createDirectoryStructure();

private:
    std::string getStemDirectory();
    std::vector<std::string> getSubdirectoryNames();
    void createSubdirectories(const std::string &stemDir, const std::vector<std::string> &subDirNames);
};

#endif // DIRECTORY_CREATOR_H