#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <set>
#include <deque>
#include <algorithm>

struct tree {
    int32_t xCord;
    int32_t yCord;
    int32_t height;
};

typedef std::vector<std::vector<tree>> grid;

tree newTree(const int32_t& iniX, const int32_t& iniY, const int32_t& iniHeight);
std::set<tree> visibleTrees(const std::deque<tree>& treeLine);
uint32_t scenicTrees(const grid& trees, const tree& currentLocation);

bool operator==(const tree& lhs, const tree& rhs);
bool operator<(const tree& lhs, const tree& rhs);
void resetTree(tree* ref);

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> forestGrid(in, eof);

    std::vector<tree> inputVec;
    grid trees;
    tree inputTree;

    std::vector<std::deque<tree>> treeLines;
    std::deque<tree> tempDeque;

    std::set<tree> partOne, tempSet;


    for (int32_t y = 0; y < forestGrid.size(); y++) {
        for (int32_t x = 0; x < forestGrid[y].size(); x++) {
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
    for (int32_t y = 0; y < trees.size(); y++) {
        for (int32_t x = 0; x < trees[y].size(); x++) {
            tempDeque.push_back(trees[y][x]);
        }
        tempDeque.push_front(inputTree);
        tempDeque.push_back(inputTree);
        treeLines.push_back(tempDeque);
        tempDeque.clear();
    }

    for (int32_t x = 0; x < trees[0].size(); x++) {
        for (int32_t y = 0; y < trees.size(); y++) {
            tempDeque.push_back(trees[y][x]);
        }
        tempDeque.push_front(inputTree);
        tempDeque.push_back(inputTree);
        treeLines.push_back(tempDeque);
        tempDeque.clear();
    }

    for (const auto& line : treeLines) {
        tempSet = visibleTrees(line);
        partOne.insert(tempSet.begin(), tempSet.end());
    }

    uint32_t maximumScene = 0;
    uint32_t tempScene = 0;
    for (const auto& row : trees) {
        for (const auto& ptr : row) {
            tempScene = scenicTrees(trees, ptr);
            maximumScene = (maximumScene < tempScene) ? tempScene : maximumScene;
        }
    }

    std::cout << "Part One: " << partOne.size() << std::endl;
    std::cout << "Part Two: " << maximumScene << std::endl;

    return 0;
}

tree newTree(const int32_t& iniX, const int32_t& iniY, const int32_t& iniHeight) {
    tree tempTree;
    tempTree.xCord = iniX;
    tempTree.yCord = iniY;
    tempTree.height = iniHeight;
    return tempTree;
}

void resetTree(tree* ref) {
    ref->height = -1;
    ref->xCord = 0;
    ref->yCord = 0;
}

bool operator<(const tree& lhs, const tree& rhs) { // Sort based on X coordinates first, Y coordinates second
    if (lhs.xCord == rhs.xCord) return (lhs.yCord < rhs.yCord);
    return (lhs.xCord < rhs.xCord);
}

bool operator==(const tree& lhs, const int32_t& rhs) {
    return (lhs.height == rhs) ? 1 : 0;
}

std::set<tree> visibleTrees(const std::deque<tree>& treeLine) {
    std::set<tree> tempSet;

    auto comp = [](const tree& lhs, const tree& rhs) -> bool { return (lhs.height < rhs.height); }; // Define a comparison for the maximum height search
    int32_t maximumHeight = std::max_element(treeLine.begin(), treeLine.end(), comp)->height;      // Find the maximum height in the current set
    auto searchLimit = std::find(treeLine.rbegin(), treeLine.rend(), maximumHeight);                // Find the point at which the maximum height is reached from the opposite direction

    int32_t currentMax = 10;

    for (const auto& ptr : treeLine) {
        if (currentMax == 10) {
            currentMax =  (ptr).height;
            tempSet.insert(ptr);
        }
        else {
            if (ptr.height > currentMax) {
                currentMax = ptr.height;
                tempSet.insert(ptr);
            }
        }
        if (ptr.height == maximumHeight) break;
    }

    currentMax = 10;

    for (auto ptr = treeLine.rbegin(); ptr != searchLimit + 1; ptr++) {
        if (currentMax == 10) {
            currentMax =  (ptr)->height;
            tempSet.insert(*ptr);
        }
        else {
            if (ptr->height > currentMax) {
                currentMax = ptr->height;
                tempSet.insert(*ptr);
            }
        }
    }

    return tempSet;
}

uint32_t scenicTrees(const grid& trees, const tree& currentLocation) {
    if (currentLocation.xCord == 0 || currentLocation.yCord == 0 || currentLocation.xCord == trees[0].size() - 1 || currentLocation.yCord == trees.size() - 1) return 0;

    uint32_t scenicScore = 1;
    uint32_t viewedTrees = 0;
    bool stop = false;

    int32_t x = currentLocation.xCord;
    int32_t y = currentLocation.yCord;
    uint32_t height = currentLocation.height;

    // Look Up
    // while (--y >= 0 && trees[y][x].height < height) viewedTrees++;
    while (--y >= 0 && !stop) {
        if (trees[y][x].height >= height) stop = true;
        viewedTrees++;
    }
    if (viewedTrees != 0) scenicScore *= viewedTrees;
    viewedTrees = 0;
    stop = false;

    // Look Left
    y = currentLocation.yCord;
    // while (--x >= 0 && trees[y][x].height < height) viewedTrees++;
    while (--x >= 0 && !stop) {
        if (trees[y][x].height >= height) stop = true;
        viewedTrees++;
    }
    if (viewedTrees != 0) scenicScore *= viewedTrees;
    viewedTrees = 0;
    stop = false;

    // Look Down
    x = currentLocation.xCord;
    //while (++y <= trees.size() - 1 && trees[y][x].height < height) viewedTrees++;
    while (++y <= trees.size() - 1 && !stop) {
        if (trees[y][x].height >= height) stop = true;
        viewedTrees++;
    }
    if (viewedTrees != 0) scenicScore *= viewedTrees;
    viewedTrees = 0;
    stop = false;

    // Look Right
    y = currentLocation.yCord;
    //while (++x <= trees[y].size() - 1 && trees[y][x].height < height) viewedTrees++;
    while (++x <= trees[y].size() - 1 && !stop) {
        if (trees[y][x].height >= height) stop = true;
        viewedTrees++;
    }
    if (viewedTrees != 0) scenicScore *= viewedTrees;
    viewedTrees = 0;
    stop = false;

    return scenicScore;
}