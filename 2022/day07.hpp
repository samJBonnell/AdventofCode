#ifndef DAY_07
#define DAY_07

#include <string>
#include <vector>
#include <algorithm>

struct File {
    std::string name;
    uint32_t size;
};

File createFile(std::string iniName, uint32_t iniSize) {
    File tempFile;
    tempFile.name = iniName;
    tempFile.size = iniSize;
    return tempFile;
}

class Directory {
public:
    Directory() = default;
    Directory(std::string iniName) : name(iniName) {};
    Directory(std::string iniName, Directory* iniHeader) : name(iniName), header(iniHeader) {};

    inline std::string printName() { return name; }
    inline uint32_t printSize() { return size; }

    friend bool operator==(Directory* root, std::string targetName);

    friend void addSubDirectory(Directory* root, Directory* subDir);
    friend void addFiles(Directory* root, File file);
    friend void addFiles(Directory* root, std::vector<File> files);

    friend Directory* directorySearch(Directory* root, std::string targetName, uint32_t depthOfSearchLevel);
    friend uint32_t directorySize(Directory* root);
    friend std::vector<Directory*> sizeLimitedDirectories(Directory* root, uint32_t limit);

private:
    Directory* header;
    std::vector<Directory*> subDirectories;

    std::string name;
    std::vector<File> files;
    uint32_t size = 0;
};

bool operator==(Directory* root, std::string targetName) {
    return (root->name == targetName) ? 1 : 0;
}

void addSubDirectory(Directory* root, Directory* subDir) {
    root->subDirectories.push_back(subDir);
    subDir->header = root;

    return;
}

void addFiles(Directory* root, File file) {
    root->files.push_back(file);

    return;
}

void addFiles(Directory* root, std::vector<File> files) {
    root->files.insert(root->files.end(), files.begin(), files.end());

    return;
}

Directory* directorySearch(Directory* root, std::string targetName, uint32_t depthOfSearchLevel) {
    Directory* tempDirectory = nullptr;
    Directory* tempDirectory2 = nullptr;

    if (root == targetName) tempDirectory = root;
    for (auto ptr : root->subDirectories) {
        if (ptr == targetName) tempDirectory = ptr;
        else {
            tempDirectory2 = directorySearch(ptr, targetName, depthOfSearchLevel + 1);
            tempDirectory = (tempDirectory2 != nullptr) ? tempDirectory2 : tempDirectory;
        }
    }

    if (!depthOfSearchLevel && tempDirectory == nullptr) tempDirectory = root;
    return tempDirectory;
}

uint32_t directorySize(Directory* root) {
    for (auto ptr : root->subDirectories) {
        root->size += directorySize(ptr);
    }

    for (const auto file : root->files) {
        root->size += file.size;
    }

    return root->size;
}

std::vector<Directory*> sizeLimitedDirectories(Directory* root, uint32_t limit) {
    std::vector<Directory* > tempVec, returnVec;

    for (const auto ptr : root->subDirectories) {
        returnVec = sizeLimitedDirectories(ptr, limit);
        tempVec.insert(tempVec.end(), returnVec.begin(), returnVec.end());
    }

    if (root->size <= limit) tempVec.push_back(root);
    return tempVec;
}

#endif