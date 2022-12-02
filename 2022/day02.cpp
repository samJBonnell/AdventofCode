#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>

int main(void) {
    std::map<char, char> winningCombinations;
    std::map<char, char> tieingCombinations;
    std::map<char, char> losingCombinations;

    winningCombinations.insert({'A','Y'});
    winningCombinations.insert({'C','X'});
    winningCombinations.insert({'B','Z'});

    tieingCombinations.insert({'A','X'});
    tieingCombinations.insert({'B','Y'});
    tieingCombinations.insert({'C','Z'});

    losingCombinations.insert({'B','X'});
    losingCombinations.insert({'A','Z'});
    losingCombinations.insert({'C','Y'});

    std::string inputString;
    uint64_t score = 0;
    uint64_t scoreTwo = 0;
    char previousPlay;

    while (std::getline(std::cin, inputString)) {
        if (winningCombinations[inputString[0]] == inputString[2]) score += 6;  // Win
        if (tieingCombinations[inputString[0]] == inputString[2]) score += 3;    // Draw

        switch(inputString[2]) {
            case 'X': // Lose
                score += 1;
                previousPlay = losingCombinations[inputString[0]];
                break;
            case 'Y': // Draw
                score += 2;
                scoreTwo += 3;
                previousPlay = tieingCombinations[inputString[0]];
                break;
            case 'Z': // Win
                score += 3;
                scoreTwo += 6;
                previousPlay = winningCombinations[inputString[0]];
                break;
            default:
                break;
        }

        switch(previousPlay) {
            case 'X':
                scoreTwo += 1;
                break;
            case 'Y':
                scoreTwo += 2;
                break;
            case 'Z':
                scoreTwo += 3;
                break;
        }
    }

    std::cout << "Part One:" << std::endl << "Score: " << score << std::endl << std::endl;
    std::cout << "Part Two:" << std::endl << "Score: " << scoreTwo << std::endl;

    return 0;
}

