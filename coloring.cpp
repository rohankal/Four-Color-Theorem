#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
const std::string COLOR_CYAN = "\u001b[36;1m";
const std::string COLOR_MAGENTA = "\u001b[35;1m";
const std::string COLOR_BLUE = "\u001b[34;1m";
const std::string COLOR_YELLOW = "\u001b[33;1m";
const std::string COLOR_GREEN = "\u001b[32;1m";
const std::string COLOR_RED = "\u001b[31;1m";
const std::string COLOR_RESET = "\u001b[0m";

void createMap(std::string, int*, int*, int*, std::string**);                                            // works
void printMap(std::string**, const int, const int, const int, std::map<std::string, int>);               // works
void findNeighbors(std::string**, const int, const int, std::map<std::string, std::set<std::string>>&);  // works
void printNeighbors(std::map<std::string, std::set<std::string>>);                                       // works
bool solveMap(
        const int,
        std::map<std::string, int>&,
        std::map<std::string, std::set<std::string>>,
        int,
        std::string*);  // works
bool isValid(
        std::map<std::string, int>,
        std::map<std::string, std::set<std::string>>,
        std::string*,
        const int,
        int);                                       // works
void printFinalColors(std::map<std::string, int>);  // works

int main(int argc, char** argv) {
    std::string** map;  // declare and dynamically allocate a 2D array of strings that will represent the map being read
                        // from a text file
    map = new std::string*[80];
    int numCountries, numRows, numCols;
    for (int i = 0; i < 80; i++) {
        map[i] = new std::string[80];
    }
    std::map<std::string, std::set<std::string>> neighbors;  // map a given country to a set of its neighbors
    std::string possibleCountries[15]
            = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"};  // maximum 15 countries
                                                                                            // within a map
    std::map<std::string, int> countryColors;  // the current state of countries and the colors they correspond with
    createMap(
            argv[1],
            &numCountries,
            &numRows,
            &numCols,
            map);  // populate the 2D array and find the number of countries and other important information
    for (int i = 0; i < numCountries; i++) {  //
        std::set<std::string> rhs;
        neighbors.insert(std::pair<std::string, std::set<std::string>>(possibleCountries[i], rhs));
        countryColors.insert(std::pair<std::string, int>(possibleCountries[i], 0));
    }
    printMap(map, numCountries, numRows, numCols, countryColors);
    findNeighbors(map, numRows, numCols, neighbors);
    // printNeighbors(neighbors);
    solveMap(
            numCountries,
            countryColors,
            neighbors,
            0,
            possibleCountries);       // recursive backtracking which allows us to find the solution to any given map
    printFinalColors(countryColors);  // couts the final set of colors (the solution)
    printMap(map, numCountries, numRows, numCols, countryColors);
    for (int i = 0; i < 80; i++) {  // delete the 2D array that was dynamically allocated
        delete[] map[i];
    }
    delete[] map;
    return 0;
}

void createMap(
        std::string filename,
        int* numberOfCountries,
        int* numberOfRows,
        int* numberOfColumns,
        std::string** mapOfCountries) {  // read in from a specified filename and populate the 2D array
    std::ifstream infile(filename);
    infile >> *numberOfCountries >> *numberOfRows >> *numberOfColumns;
    std::string currentLine;
    getline(infile, currentLine);
    for (int i = 0; i < *numberOfRows; i++) {
        getline(infile, currentLine);
        currentLine.erase(currentLine.find_last_not_of(" \t\n\r\f\v") + 1);
        for (int j = 0; j < *numberOfColumns; j++) {
            mapOfCountries[i][j] = currentLine[j];
        }
    }
    infile.close();
}

void printMap(
        std::string** mapOfCountries,
        const int numCountries,
        const int numRows,
        const int numCols,
        std::map<std::string, int> countryColors) {  // print the 2D array for visualization purposes, color
                                                     // functionality was added for fun
    std::cout << '\n' << numCountries << " " << numRows << " " << numCols << std::endl;
    int currentColor = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            // std::cout << mapOfCountries[i][j];
            currentColor = countryColors[mapOfCountries[i][j]];
            if (currentColor == 0)
                std::cout << mapOfCountries[i][j];
            if (currentColor == 1)
                std::cout << COLOR_RED << mapOfCountries[i][j] << COLOR_RESET;
            if (currentColor == 2)
                std::cout << COLOR_YELLOW << mapOfCountries[i][j] << COLOR_RESET;
            if (currentColor == 3)
                std::cout << COLOR_GREEN << mapOfCountries[i][j] << COLOR_RESET;
            if (currentColor == 4)
                std::cout << COLOR_BLUE << mapOfCountries[i][j] << COLOR_RESET;
        }
        std::cout << std::endl;
    }
}

void findNeighbors(
        std::string** map,
        const int numRows,
        const int numCols,
        std::map<std::string, std::set<std::string>>&
                neighbors) {  // loop through the entire 2D array, peeking to the left/right/up/down at every given
                              // location and finding neighbors for all countries
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int aboveRow = i - 1;
            int aboveCol = j;
            int belowRow = i + 1;
            int belowCol = j;
            int leftRow = i;
            int leftCol = j - 1;
            int rightRow = i;
            int rightCol = j + 1;
            // making sure the neighboring indices are within bounds
            if (aboveRow < 0) {
                aboveRow = 0;
            }
            if (belowRow == numRows) {
                belowRow = numRows - 1;
            }
            if (leftCol < 0) {
                leftCol = 0;
            }
            if (rightCol == numCols) {
                rightCol = numCols - 1;
            }
            // extracting the countries at neighboring indices
            std::string currentLetter = map[i][j];
            std::string aboveLetter = map[aboveRow][aboveCol];
            std::string belowLetter = map[belowRow][belowCol];
            std::string leftLetter = map[leftRow][leftCol];
            std::string rightLetter = map[rightRow][rightCol];
            //...checking if the countries are any different
            if (currentLetter != aboveLetter) {
                neighbors[currentLetter].insert(aboveLetter);
            }
            if (currentLetter != belowLetter) {
                neighbors[currentLetter].insert(belowLetter);
            }
            if (currentLetter != leftLetter) {
                neighbors[currentLetter].insert(leftLetter);
            }
            if (currentLetter != rightLetter) {
                neighbors[currentLetter].insert(rightLetter);
            }
        }
    }
}

void printNeighbors(
        std::map<std::string, std::set<std::string>> neighbors) {  // go through each of the countries and print their
                                                                   // neighbors in a neat, understandable manner
    for (std::map<std::string, std::set<std::string>>::const_iterator it = neighbors.begin(); it != neighbors.end();
         ++it) {
        std::cout << it->first << ":";
        for (auto it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
            std::cout << " " << *it2;
        }
        std::cout << "\n";
    }
}

bool solveMap(
        const int numCountries,
        std::map<std::string, int>& countryColors,
        std::map<std::string, std::set<std::string>> neighbors,
        int countryToColor,
        std::string* possibleCountries) {
    bool solutionFound = true;
    for (int i = 0; i < numCountries; i++) {  // check if the colors have all been found (if you have any zeros that
                                              // means we still need to look for colors)
        if (countryColors[possibleCountries[i]] == 0) {
            solutionFound = false;
            break;
        }
    }
    if (solutionFound == true) {  // if we have found a solution, return true
        return true;
    }
    for (int i = 1; i <= 4; i++) {  // for any given country, loop through all possible color possibilities
        countryColors[possibleCountries[countryToColor]] = i;
        if (isValid(countryColors,
                    neighbors,
                    possibleCountries,
                    numCountries,
                    countryToColor)) {  // check if the color placement is valid
            if (solveMap(
                        numCountries,
                        countryColors,
                        neighbors,
                        countryToColor + 1,
                        possibleCountries)) {  // if it is...recur to the next country and return true if you are
                                               // eventually able to find a solution
                return true;
            }
        }
        countryColors[possibleCountries[countryToColor]]
                = 0;  // remove the color you placed so that you can backtrack accurately
    }
    return false;  // solution not found
}

bool isValid(
        std::map<std::string, int> countryColors,
        std::map<std::string, std::set<std::string>> neighbors,
        std::string* possibleCountries,
        const int numCountries,
        int countryToColor) {  // for every country, makes sure that its color is not equal to the color of any one of
                               // its neighbors
    int currentColor = countryColors[possibleCountries[countryToColor]];
    int neighborColor;
    std::set<std::string> currentNeighbors = neighbors[possibleCountries[countryToColor]];
    std::set<std::string>::iterator it;
    for (it = currentNeighbors.begin(); it != currentNeighbors.end(); ++it) {
        neighborColor = countryColors[*it];
        if (neighborColor == currentColor) {  // if they're the same color...the color placement is not valid
            return false;
        }
    }
    return true;
}

void printFinalColors(std::map<std::string, int> countryColors) {  // cout the final color scheme that solves the map
    for (auto it = countryColors.cbegin(); it != countryColors.cend(); ++it) {
        std::cout << (*it).first << " " << (*it).second << "\n";
    }
}