#ifndef DAY_07
#define DAY_07

#include <iostream>
#include <vector>
#include <string>

struct File {
    uint64_t size;
    std::string name;
};

class Directory {
public:
    Directory() = default;
    Directory(Directory* header, std::string inName) : headPointer(header), name(inName) {};

    inline void addSubDirectory(std::string iniName) {
        Directory tempDirectory(this, iniName);
        subDirectories.push_back(tempDirectory);
    };
    inline void addFiles(File file) {files.push_back(file); };

    friend Directory* searchDirectories(Directory* root, const std::string target, uint32_t level);
    friend uint64_t sumDirectories(Directory* masterPointer);
    friend std::vector<Directory*> limitedDirectories(Directory* masterPointer, const uint64_t limit);
    friend std::string printDirName(Directory* dir);

    friend bool operator==(const Directory* lhs, const std::string& rhs);
    friend bool operator==(const Directory lhs, const std::string& rhs);
    friend bool operator!=(const Directory* lhs, const std::string& rhs);

private:
    std::string name;
    std::vector<Directory> subDirectories;
    std::vector<File> files;
    Directory* headPointer = nullptr;
};

bool operator==(const Directory* lhs, const std::string& rhs) {
    return (lhs->name == rhs) ? 1 : 0;
}

bool operator==(const Directory lhs, const std::string& rhs) {
    return (lhs.name == rhs) ? 1 : 0;
}

bool operator!=(const Directory* lhs, const std::string& rhs) {
    return (lhs->name != rhs) ? 1 : 0;
}

Directory* searchDirectories(Directory* root, const std::string target, uint32_t level) {
    Directory* tempPointer = nullptr;

    if (root == target) tempPointer = root;
    for (auto dir : root->subDirectories) {
        if (dir == target) { // If the directory is the correct one
            tempPointer = &dir;
            return tempPointer;
        }
        tempPointer = searchDirectories(&dir, target, level + 1);
    }
    
    if (!level) tempPointer = root;
    return tempPointer;
}

uint64_t sumDirectories(Directory* root) {
    uint64_t tempSum = 0;
    for (auto dir : root->subDirectories) {
        tempSum += sumDirectories(&dir);
    }

    for (const auto& file : root->files) {
        tempSum += file.size;
    }

    return tempSum;
}

std::vector<Directory*> limitedDirectories(Directory* root, const uint64_t limit) {
    std::vector<Directory* > tempVec, tempVec2;

    for (auto dir : root->subDirectories) {
        tempVec2 = limitedDirectories(&dir, limit);
        tempVec.insert(std::end(tempVec), std::begin(tempVec2), std::end(tempVec2));
    }

    if (sumDirectories(root) <= limit) tempVec.push_back(root);

    return tempVec;
}

std::string printDirName(Directory* dir) {
    return dir->name;
}

File createFile(std::string inName, uint64_t inSize) {
    File tempFile;
    tempFile.name = inName;
    tempFile.size = inSize;

    return tempFile;
}

#endif