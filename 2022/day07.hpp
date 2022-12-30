#ifndef DAY_07
#define DAY_07

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

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

    inline std::string dirName() { return name; }
    inline uint32_t dirSize() { return size; }
    inline Directory* dirHeader() { return header; }

    friend bool operator==(Directory* root, std::string targetName);

    friend void addSubDirectory(Directory* root, Directory* subDir);
    friend void addFiles(Directory* root, File file);
    friend void addFiles(Directory* root, std::vector<File> files);

    friend Directory* directorySearch(Directory* root, std::string targetName, uint32_t depthOfSearchLevel);
    friend uint32_t directorySize(Directory* root);
    friend std::vector<Directory*> sizeLimitedDirectories(Directory* root, uint32_t limit, std::function<bool(const uint32_t&, const uint32_t&)> compare);
    friend void printStructure(Directory* root, uint32_t depthOfCallIndex);

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

std::vector<Directory*> sizeLimitedDirectories(Directory* root, uint32_t limit, std::function<bool(const uint32_t&, const uint32_t&)> compare) {
    std::vector<Directory* > tempVec, returnVec;

    for (const auto ptr : root->subDirectories) {
        returnVec = sizeLimitedDirectories(ptr, limit, compare);
        tempVec.insert(tempVec.end(), returnVec.begin(), returnVec.end());
    }

    if (compare(root->size, limit)) tempVec.push_back(root);
    return tempVec;
}

void printStructure(Directory* root, uint32_t depthOfCallIndex) {
    for (uint32_t i = 0; i < depthOfCallIndex; i++) std::cout << "  ";
    std::cout << root->name << std::endl;
    for (auto ptr : root->subDirectories) {
        printStructure(ptr, depthOfCallIndex + 1);
    }

    for (const auto& ptr : root->files) {
        for (uint32_t i = 0; i < depthOfCallIndex + 1; i++) std::cout << "  ";
        std::cout << ptr.name << " - " << ptr.size << std::endl;
    }

    return;
}

#endif