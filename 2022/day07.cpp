#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "day07.hpp"

int main(void) {
    Directory* rootDir = nullptr;
    Directory A("A");
    Directory B("B");
    Directory C("C");
    Directory D("D");

    addSubDirectory(&A, &B);
    addSubDirectory(&B, &C);
    addSubDirectory(&A, &D);

    addFiles(&A, createFile("A", 10));
    addFiles(&B, createFile("A", 20));
    addFiles(&C, createFile("C", 10));
    addFiles(&D, createFile("A", 10));

    directorySize(&A);
    
    std::vector<Directory*> limitedDirectories = sizeLimitedDirectories(&A, 300);
    std::cout << limitedDirectories.size() << std::endl;

    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> terminalInput(in, eof);
    std::string inputString;
    uint32_t index = 0;

    Directory* currentDirectory = nullptr;
    
    for (const auto& terminalLine : terminalInput) {
        std::stringstream tempStream(terminalLine);
        // Change directory mode or add file mode - do not care about ls
        /*
            Check for command mode
            If command mode:
                Check for change of directory
                if cd
                    grab string to change the directory
            If not command mode
                check for "dir"
                if "dir"
                    add directory to current directory
                if number
                    grab number and name and add file to current directory
        */

        while (std::getline(tempStream, inputString, ' ')) {
            
        }
    }

    return 0;
}