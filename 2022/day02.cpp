#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>

int main(void) {
    std::map<char, char> winningCombinations;
    std::map<char, char> tyingCombinations;
    std::map<char, char> losingCombinations;
    /*
    A : Rock    - > X : Rock    - > 1 point
    B : Paper   - > Y : Paper   - > 2 point
    C : Scissor - > Z : Scissor - > 3 point

    Win - 6
    Draw - 3
    Lose - 0

    Paper Beats Rock        -> Y,A or B,X
    Rock Beats Scissors     -> X,C or A,Z
    Scissors beat Paper     -> Z,B or C,Y

    Part Two:

    X - Lose
    Y - Draw
    Z - Win
    */

    winningCombinations.insert({'A','Y'});
    winningCombinations.insert({'C','X'});
    winningCombinations.insert({'B','Z'});

    tyingCombinations.insert({'A','X'});
    tyingCombinations.insert({'B','Y'});
    tyingCombinations.insert({'C','Z'});

    losingCombinations.insert({'B','X'});
    losingCombinations.insert({'A','Z'});
    losingCombinations.insert({'C','Y'});

    std::string inputString;
    uint64_t score = 0;
    uint64_t scoreTwo = 0;
    char previousPlay;

    while (std::getline(std::cin, inputString)) {
        if (winningCombinations[inputString[0]] == inputString[2]) score += 6;  // Win
        if (tyingCombinations[inputString[0]] == inputString[2]) score += 3;                       // Draw

        switch(inputString[2]) {
            case 'X': // Lose
                score += 1;
                previousPlay = losingCombinations[inputString[0]];
                break;
            case 'Y': // Draw
                score += 2;
                scoreTwo += 3;
                previousPlay = tyingCombinations[inputString[0]];
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

