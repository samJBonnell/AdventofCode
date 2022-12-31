#include <iostream>
#include <vector>
#include <deque>
#include <iterator>
#include <string>
#include <set>
#include <cmath>
#include <fstream>

/*
Part One: 13
R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2

Part Two: 36
R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20
*/

constexpr uint32_t CHAIN_LENGTH = 10;

struct Knot {
    int32_t x;
    int32_t y;
    
    Knot* nextKnot = nullptr;

    Knot(const int32_t& iniX, const int32_t& iniY) : x(iniX), y(iniY) {};
};

void updateKnotPositions(Knot* root);
void printVisitedLocations(std::set<Knot>& visitedLocations);

bool operator==(const Knot& lhs, const Knot& rhs);
bool operator&&(const Knot& lhs, const Knot& rhs);
bool operator<(const Knot& lhs, const Knot& rhs);

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> unparsedInput(in, eof);

    std::deque<Knot> knots;
    Knot rootKnot(0,0);
    knots.push_back(rootKnot);

    for (uint32_t it = 0; it < CHAIN_LENGTH - 1; it++) {
        Knot tempKnot(0,0);
        knots.push_back(tempKnot);
        knots[it].nextKnot = &(knots.back());
    }

    std::set<Knot> tailVisited;

    bool index = false;
    char direction;
    uint32_t moveDistance;
    for (const auto& ptr : unparsedInput) {
        if (!index) {
            direction = ptr[0];
            index = true;
        }
        else {
            moveDistance = std::stoi(ptr);
            for (uint32_t it = 0; it < moveDistance; it++) {
                switch (direction) {
                    case 'R':
                        knots.front().x += 1;
                        break;
                    case 'U':
                        knots.front().y += 1;
                        break;
                    case 'L':
                        knots.front().x -= 1;
                        break;
                    case 'D':
                        knots.front().y -= 1;
                        break;
                    default:
                        break;
                }

                // Insert tail
                tailVisited.insert(knots.back());
                
                // Update tail
                updateKnotPositions(&knots.front());
            }

            index = false;
        }
    }
    tailVisited.insert(knots.back());
    printVisitedLocations(tailVisited);

    if (CHAIN_LENGTH == 2)
        std::cout << "Part One: " <<tailVisited.size() << std::endl;
    else if (CHAIN_LENGTH == 10)
        std::cout << "Part Two: " <<tailVisited.size() << std::endl;
    else
        std::cout << "Arbitrary Chain Length: " <<tailVisited.size() << std::endl;

    return 0;
}

void updateKnotPositions(Knot* root) {
    int32_t xDistance = root->x - root->nextKnot->x;
    int32_t yDistance = root->y - root->nextKnot->y;

    if (xDistance == 0) {
        if (std::abs(yDistance) >= 2) {
            root->nextKnot->y += (yDistance / 2);
        }
    }
    else if (yDistance == 0) {
        if (std::abs(xDistance) >= 2) {
            root->nextKnot->x += (xDistance / 2);
        }
    }
    else if (xDistance != 0 && yDistance != 0 ) {
        if (std::abs(xDistance) >= 2 || std::abs(yDistance) >= 2) {
            if (std::abs(xDistance) > std::abs(yDistance)) {
                root->nextKnot->x += (xDistance / 2);
                root->nextKnot->y += yDistance;
            }
            else {
                root->nextKnot->x += xDistance;
                root->nextKnot->y += (yDistance / 2);
            }
        }
    }

    if (root->nextKnot->nextKnot != nullptr) updateKnotPositions(root->nextKnot);

    return;
}

void printVisitedLocations(std::set<Knot>& visitedLocations) {
    std::ofstream outputFile;
    outputFile.open("output.txt");

    int32_t width = visitedLocations.rbegin()->x - visitedLocations.begin()->x;
    int32_t xOffset = visitedLocations.begin()->x;
    int32_t yOffset = 0, maximum = 0;
    for (const auto& ptr : visitedLocations) {
        yOffset = (ptr.y < yOffset) ? ptr.y : yOffset;
        maximum = (ptr.y > maximum) ? ptr.y : maximum;
    }

    std::vector<std::vector<char>> outputBoard(maximum - yOffset + 1, std::vector<char>(width + 1, '.'));
    for (const auto& ptr : visitedLocations) {
        outputBoard[ptr.y - yOffset][ptr.x - xOffset] = 'X';
    }

    outputBoard[std::abs(yOffset)][std::abs(xOffset)] = 's';

    for (auto ptr = outputBoard.rbegin(); ptr != outputBoard.rend(); ptr++) {
        for (const auto& column : *ptr) {
            //std::cout << column;
            outputFile << column;
        }
        //std::cout << std::endl;
        outputFile << std::endl;
    }

    outputFile.close();
}

bool operator==(const Knot& lhs, const Knot& rhs) { // Check to see if they are in the same row
    return (lhs.x == rhs.x);
}

bool operator&&(const Knot& lhs, const Knot& rhs) { // Check to see if they are in the same rows and columns
    return (lhs.x == rhs.x || lhs.y == rhs.y);
}

bool operator<(const Knot& lhs, const Knot& rhs) { // Sort based on X coordinates first, Y coordinates second
    if (lhs.x == rhs.x) return (lhs.y < rhs.y);
    return (lhs.x < rhs.x);
}