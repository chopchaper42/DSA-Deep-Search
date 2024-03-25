#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "maze.h"
//#include "Plate.h"


using namespace std;

/*
bool containsInvalidSymbols(string str) {
    return any_of(str.begin(), str.end(), [](char c) { return c != '.' && c != '#'; });
}

bool hasErrors(const vector<string> &rows) {
    for (int i = 0; i < rows.size(); i++) {
        const string &row = rows[i];

        if (!rows.empty() && row.size() != rows[0].size()) {
            cerr << "Error: Bludiste neni obdelnikove!" << '\n';
            return true;
        }
    }

    for (int i = 0; i < rows.size(); i++) {
        string row = rows[i];

        if (i == rows.size() - 1) {
            if (row[row.size() - 2] != '.') {
                cerr << "Error: Vystup neni vpravo dole!" << '\n';
                return true;
            }
        }

        if (i == 0) {
            if (row[1] != '.') {
                cerr << "Error: Vstup neni vlevo nahore!" << '\n';
                return true;
            }
        }
    }

    for (int i = 0; i < rows.size(); i++) {
        string row = rows[i];


        if (containsInvalidSymbols(row)) { // encapsulate with try/catch
            cerr << "Error: Bludiste obsahuje nezname znaky!" << '\n';
            return true;
        }

        if (row.size() < 5 || row.size() > 100) {
            cerr << "Error: Sirka bludiste je mimo rozsah!" << '\n';
            return true;
        }

        if (rows.size() < 5 || rows.size() > 50) {
            cerr << "Error: Delka bludiste je mimo rozsah!" << '\n';
            return true;
        }



        if (i == 0) {

            for (int j = 0; j < row.size(); j++) {
                if (j == 1) continue;
                if (row[j] != '#') {
                    cerr << "Error: Bludiste neni oplocene!" << '\n';
                    return true;
                }
            }
        }

        if (i == rows.size() - 1) {
            for (int j = 0; j < row.size(); j++) {
                if (j == row.size() - 2) continue;
                if (row[j] != '#') {
                    cerr << "Error: Bludiste neni oplocene!" << '\n';
                    return true;
                }
            }
        }
    }
    return false;
}
// TODO: add error "no path exists".




Maze* createMaze() {
    string line;
    size_t width = 0;
    vector<string> rows;

    while (cin >> line) {
        if (width == 0)
            width = line.size();
        rows.push_back(line);
    }

    if (hasErrors(rows))
        throw std::domain_error("Error in the maze structure.");

    Plate*** plates = new Plate**[rows.size()];

    for (int i = 0; i < rows.size(); ++i) {
        plates[i] = new Plate*[width];
    }

    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < width; ++j) {
            bool road = rows[i][j] == '.';
            plates[i][j] = new Plate(j, i, road);
        }
    }

    return new Maze(width, rows.size(), plates);
}

Maze::Maze(int width, int height, Plate ***maze): width{width}, height{height}, maze{maze} {}

Maze::~Maze() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete maze[i][j];
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

int Maze::getHeight() const { return height; }
int Maze::getWidth() const { return width; }
Plate*** Maze::getPlates() { return maze; }

*/
/*void Maze::buildTree(Plate &plate) {
    plate.addNeighbors(maze, width, height);

    if (isAnExit(plate))
        return;

    for (auto &neighbor : plate.getNeighbors()) {
        if (neighbor.getNeighbors().empty())
            buildTree(neighbor);
    }
}*//*


bool Maze::isAnExit(Plate plate) const {
    return plate.getY() == height - 1 && plate.getX() == width - 2;
}
*/
