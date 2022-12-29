#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "day07.hpp"

int main(void) {
    /*
    std::istream_iterator<std::string> in(std::cin), end;
    std::vector<std::string> terminalOutput(in, end);
    */

    std::vector<Directory> directories;

    Directory A(nullptr, "A");
    A.addSubDirectory("B");
    A.addSubDirectory("C");

    Directory* masterPointer = searchDirectories(&A, "C", 0);
    std::cout << printDirName(masterPointer) << std::endl;

    masterPointer->addSubDirectory("D");

    masterPointer = searchDirectories(&A, "D", 0);

    return 0;
}