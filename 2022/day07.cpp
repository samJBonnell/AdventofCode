#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iterator>
#include <sstream>

#include "day07.hpp"

constexpr uint32_t COMMAND = 1;
constexpr uint32_t CD = 2;
constexpr uint32_t LS = 3;
constexpr uint32_t DIR_MODE = 4; 
constexpr uint32_t FILE_MODE = 5;

constexpr uint32_t DISK_SIZE = 70000000;
constexpr uint32_t REQU_SIZE = 30000000;

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> terminalInput(in, eof);

    std::deque<Directory> fileStructure;
    std::vector<Directory*> limitedDirectories;

    std::string inputString;
    std::string mpString; // Multipurpose input string
    uint32_t index = 0;

    Directory directoryBase("/", nullptr);
    Directory* currentDirectory = &directoryBase;

    File tempFile;
    
    for (const auto& input : terminalInput) {
        if (input == "$") index = COMMAND; // A command will be registered!
        else if (index == COMMAND) {
            if (input == "cd") index = CD; // Change directory
            else if (input == "ls") index = LS; // List directory layout
        }
        else if (index == CD) { // Change current directory level
            if (input == "..") {
                currentDirectory = currentDirectory->dirHeader();
            }
            else currentDirectory = directorySearch(currentDirectory, input, 0); // Set the current directory to the one required by the input command
        }
        else { // Not a command but instead an input!
            if (index == DIR_MODE) {
                Directory tempDir(input);
                fileStructure.push_back(tempDir);
                addSubDirectory(currentDirectory, &fileStructure.back());
                index = LS;
            }
            else if (index == FILE_MODE) {
                tempFile.name = input;
                addFiles(currentDirectory, tempFile);
                index = LS;
            } 
            else if (input == "dir") index = DIR_MODE;
            else if (is_number(input)) {
                index = FILE_MODE;
                tempFile.size = std::stoi(input);
            }
        }
    }

    directorySize(&directoryBase);
    limitedDirectories = sizeLimitedDirectories(&directoryBase, 100000, [](uint32_t lhs, uint32_t rhs) -> bool { return (lhs <= rhs); });

    uint32_t totalSize = 0;
    for (const auto ptr : limitedDirectories) {
        totalSize += ptr->dirSize();
    }

    uint32_t requiredSize = REQU_SIZE - (DISK_SIZE - directoryBase.dirSize());
    uint32_t smallestDir = 0;
    limitedDirectories = sizeLimitedDirectories(&directoryBase, requiredSize, [](uint32_t lhs, uint32_t rhs) -> bool { return (lhs >= rhs); });
    for (const auto& ptr : limitedDirectories) {
        if (smallestDir == 0) smallestDir = ptr->dirSize();
        else {
            smallestDir = (ptr->dirSize() < smallestDir) ? ptr->dirSize() : smallestDir;
        }
    }

    std::cout << "Part One" << std::endl;
    std::cout << totalSize << std::endl;

    std::cout << std::endl;
    std::cout << "Part Two" << std::endl;
    std::cout << smallestDir << std::endl;

    std::cout << std::endl;
    printStructure(&directoryBase, 0);

    return 0;
}