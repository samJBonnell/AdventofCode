#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <set>
#include <deque>

/*
    For each interior row and column, progress until a point lower than or equal to the previous height is found
    Move to the other side of the row/column and repeat

    Add all visible trees to the set of all trees

    tree a = newTree(1,0,0);
    tree b = newTree(2,0,1);
    tree c = newTree(3,0,3);
    tree d = newTree(4,0,2);
    tree e = newTree(5,0,2);
    tree f = newTree(6,0,1);
    tree g = newTree(7,0,0);

    std::vector<tree> test;

    test.push_back(a);
    test.push_back(b);
    test.push_back(c);
    test.push_back(d);
    test.push_back(e);
    test.push_back(f);
    test.push_back(g);

    std::set<tree> test2 = visibleTrees(test);

*/

struct tree {
    uint32_t xCord;
    uint32_t yCord;
    uint32_t height;
};

typedef std::vector<std::vector<tree>> grid;

tree newTree(const uint32_t& iniX, const uint32_t& iniY, const uint32_t& iniHeight);
std::set<tree> visibleTrees(const std::deque<tree>& treeLine);
void resetTree(tree* ref);

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> forestGrid(in, eof);

    std::vector<tree> inputVec;
    grid trees;
    tree inputTree;

    for (uint32_t y = 0; y < forestGrid.size(); y++) {
        for (uint32_t x = 0; x < forestGrid[y].size(); x++) {
            inputTree.height = forestGrid[y][x] - '0';
            inputTree.xCord = x;
            inputTree.yCord = y;

            inputVec.push_back(inputTree);
        }
        trees.push_back(inputVec);
        inputVec.clear();
        resetTree(&inputTree);
    }

    // Traverse once over the rows, and once over the columns
    std::vector<std::deque<tree>> treeLines;
    std::deque<tree> tempDeque;

    for (uint32_t y = 1; y < trees.size() - 1; y++) {
        for (uint32_t x = 0; x < trees[y].size(); x++) {
            tempDeque.push_back(trees[y][x]);
        }
        //tempDeque.push_front(inputTree);
        //tempDeque.push_back(inputTree);
        treeLines.push_back(tempDeque);
        tempDeque.clear();
    }

    for (uint32_t x = 1; x < trees[0].size() - 1; x++) {
        for (uint32_t y = 0; y < trees.size(); y++) {
            tempDeque.push_back(trees[y][x]);
        }
        //tempDeque.push_front(inputTree);
        //tempDeque.push_back(inputTree);
        treeLines.push_back(tempDeque);
        tempDeque.clear();
    }

    std::set<tree> partOne, tempSet;
    for (const auto& line : treeLines) {
        tempSet = visibleTrees(line);
        partOne.insert(tempSet.begin(), tempSet.end());
    }

    std::cout << "Part One: " << partOne.size() << std::endl;

    return 0;
}

tree newTree(const uint32_t& iniX, const uint32_t& iniY, const uint32_t& iniHeight) {
    tree tempTree;
    tempTree.xCord = iniX;
    tempTree.yCord = iniY;
    tempTree.height = iniHeight;
    return tempTree;
}

void resetTree(tree* ref) {
    ref->height = 0;
    ref->xCord = 0;
    ref->yCord = 0;
}

bool operator<(const tree& lhs, const tree& rhs) { // Sort based on X coordinates first, Y coordinates second
    if (lhs.xCord == rhs.xCord) return (lhs.yCord < rhs.yCord);
    if (lhs.yCord == rhs.yCord) return (lhs.xCord < rhs.xCord);
    return (lhs.xCord < rhs.xCord);

    // If the x axis are the same, 
}

std::set<tree> visibleTrees(const std::deque<tree>& treeLine) {
    std::set<tree> tempSet;
    uint32_t currentHighest = 10;

    for (auto it_f = treeLine.begin(); it_f != treeLine.end(); it_f++) {
        if (currentHighest == 10) {
            currentHighest = (it_f)->height;
        }
        else if ((it_f)->height > currentHighest) {
            tempSet.insert(*(it_f));
            currentHighest = (it_f)->height;
        }
    }

    currentHighest = 10;

    for (auto it_r = treeLine.rbegin(); it_r != treeLine.rend(); it_r++) {
        if (currentHighest == 10) {
            currentHighest = (it_r)->height;
        }
        else if ((it_r)->height > currentHighest) {
            tempSet.insert(*(it_r));
            currentHighest = (it_r)->height;
        }
    }

    return tempSet;
}