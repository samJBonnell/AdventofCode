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



private:
    std::string name;
    std::vector<Directory *> subDirectories;
    std::vector<File> files;
};

#endif