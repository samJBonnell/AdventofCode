#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <set>

/*

9 - 11
6 - 7
3 - 3

*/

int main(void) {
    std::string tempString;
    std::vector<std::vector<char>> crates;
    std::vector<std::string> moves;
    std::set<uint32_t> cols;

    bool firstRow = 0;

    while (std::getline(std::cin,tempString)) {
        if (!firstRow) {
            int32_t i = tempString.length() - 1;
            while (i > 0 ) {
                cols.insert(i);
                std::cout << i << std::endl;
                i -= 4;
            }

            std::vector<char> tempVector;
            
        }

        
    }


    return 0;
}