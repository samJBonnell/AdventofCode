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
    Directory(std::string inName) : name(inName) {};

    inline void addSubDirectory(Directory* directory) {subDirectories.push_back(directory); };
    inline void addFiles(File file) {files.push_back(file); };

    inline std::ostream& outputName(std::ostream& stream) { 
        stream << this->name;
        return stream;
    };

    friend void searchDirectories(Directory* root, const std::string target, bool& found);
    friend uint64_t sumDirectories(Directory* root);
    friend bool operator==(const Directory* lhs, const std::string& rhs);
    friend bool operator==(const Directory lhs, const std::string& rhs);
    friend bool operator!=(const Directory* lhs, const std::string& rhs);

private:
    std::string name;
    std::vector<Directory *> subDirectories;
    std::vector<File> files;
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

void searchDirectories(Directory* root, const std::string target, bool& found) {
    if (root == target) found = true;
    for (const auto dir : root->subDirectories) {
        if (dir == target) { // If the directory is the correct one
            root = dir;
            found = true;
            return;
        }
        searchDirectories(dir, target, found);
        if (found) return;
    }
}

uint64_t sumDirectories(Directory* root) {
    uint64_t tempSum = 0;
    for (const auto dir : root->subDirectories) {
        tempSum += sumDirectories(dir);
    }

    for (const auto& file : root->files) {
        tempSum += file.size;
    }

    return tempSum;
}

File createFile(std::string inName, uint64_t inSize) {
    File tempFile;
    tempFile.name = inName;
    tempFile.size = inSize;

    return tempFile;
}

#endif