#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <chrono>

bool abortion = false;

class Plate {
public:
    Plate(int x, int y, bool road): x{x}, y{y}, road{road}  {}
    ~Plate() = default;
    Plate() {}
    void unroad() { road = false; }
    void roadate() { road = true; }
    void setInOriginalRoad(bool b) { inOriginalRoad = b; }
    bool isInOriginalPath() { return inOriginalRoad; }
    void addNeighbor(Plate *plate) {
        if (plate->road)
            neighbors.push_back(plate);
    }
    void addNeighbors(Plate*** plates, int width, int height) {
        if (!road)
            return;
        /*if (!((x == 1 && y == 0) || (x == width - 2 && y == height - 1))) {
            int bushesAround = 0;

            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    if (i == 0 && j == 0) continue;
                    if (!plates[y + i][x + j]->road)
                        bushesAround++;
                }
            }
            if (bushesAround == 7) {
//                road = false;
                visited = true;
                return;
            }
        }*/
        if (x < width - 1) {
            // add the plate on the right
            addNeighbor(plates[y][x + 1]);
        }

        if (y < height - 1) {
            // add the plate below
            addNeighbor(plates[y + 1][x]);
        }

        if (x > 0) {
            // add the plate on the left
            addNeighbor(plates[y][x - 1]);
        }

        if (y > 0) {
            // add the plate above
            addNeighbor(plates[y - 1][x]);
        }

    }
    std::vector<Plate*> getNeighbors() {
        return neighbors;
    }
//    void printCoordinatesAndNeighborsNumber();
    int getX() { return x; }
    int getY() { return y; }
    bool isRoad() { return road; }
    bool isVisited() { return visited; }
    void visit() { visited = true; }
    void unvisit() { visited = false; }

private:
    int x;
    int y;
    bool road = false;
    bool visited = false;
    bool inOriginalRoad = false;
    std::vector<Plate*> neighbors;
};

class Maze {
public:
    Maze(int width, int height, Plate*** maze);
    ~Maze();
    int getWidth() const;
    int getHeight() const;
    Plate*** getPlates();
    void buildTree(Plate &plate);
    bool isAnExit(Plate plate) const;

private:
    int width;
    int height;
    Plate*** maze;
};

Maze* createMaze();

void printPlate(Maze* maze, std::vector<Plate*> &answer) {
    for (int i = 0; i < maze->getHeight(); i++) {
        for (int j = 0; j < maze->getWidth(); j++) {
            Plate * p = maze->getPlates()[i][j];
            char c = '.';

            if (!p->isRoad())
                c = '#';

            for (auto plate : answer) {
                if (plate->getX() == p->getX() && plate->getY() == p->getY()) {
//                    c = '!';
                    c = '!';
                    break;
                }
            }

            std::cout << c;

        }
        std::cout << '\n';
    }
    std::cout << "- - - - - - - - - - - - - - - \n";
}

bool containsInvalidSymbols(std::string str) {
    return std::any_of(str.begin(), str.end(), [](char c) { return c != '.' && c != '#'; });
}

bool hasErrors(const std::vector<std::string> &rows) {
    for (size_t i = 0; i < rows.size(); i++) {
        const std::string &row = rows[i];

        if (!rows.empty() && row.size() != rows[0].size()) {
            std::cerr << "Error: Bludiste neni obdelnikove!" << '\n';
            return true;
        }
    }

    for (size_t i = 0; i < rows.size(); i++) {
        std::string row = rows[i];

        if (i == rows.size() - 1) {
            if (row[row.size() - 2] != '.') {
                std::cerr << "Error: Vystup neni vpravo dole!" << '\n';
                return true;
            }
        }

        if (i == 0) {
            if (row[1] != '.') {
                std::cerr << "Error: Vstup neni vlevo nahore!" << '\n';
                return true;
            }
        }
    }

    for (size_t i = 0; i < rows.size(); i++) {
        std::string row = rows[i];


        if (containsInvalidSymbols(row)) { // encapsulate with try/catch
            std::cerr << "Error: Bludiste obsahuje nezname znaky!" << '\n';
            return true;
        }

        if (row.size() < 5 || row.size() > 100) {
            std::cerr << "Error: Sirka bludiste je mimo rozsah!" << '\n';
            return true;
        }

        if (rows.size() < 5 || rows.size() > 50) {
            std::cerr << "Error: Delka bludiste je mimo rozsah!" << '\n';
            return true;
        }



        if (i == 0) {

            for (size_t j = 0; j < row.size(); j++) {
                if (j == 1) continue;
                if (row[j] != '#') {
                    std::cerr << "Error: Bludiste neni oplocene!" << '\n';
                    return true;
                }
            }
        }

        if (i == rows.size() - 1) {
            for (size_t j = 0; j < row.size(); j++) {
                if (j == row.size() - 2) continue;
                if (row[j] != '#') {
                    std::cerr << "Error: Bludiste neni oplocene!" << '\n';
                    return true;
                }
            }
        }
    }
    return false;
}
// TODO: add error "no path exists".




Maze* createMaze() {
    std::string line;
    size_t width = 0;
    std::vector<std::string> rows;

    while (std::cin >> line) {
        if (width == 0)
            width = line.size();
        rows.push_back(line);
    }

    if (hasErrors(rows))
        throw std::domain_error("Error in the maze structure.");

    Plate*** plates = new Plate**[rows.size()];

    for (size_t i = 0; i < rows.size(); ++i) {
        plates[i] = new Plate*[width];
    }

    for (size_t i = 0; i < rows.size(); ++i) {
        for (size_t j = 0; j < width; ++j) {
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
bool Maze::isAnExit(Plate plate) const {
    return plate.getY() == height - 1 && plate.getX() == width - 2;
}


/*std::vector<Plate*> intersect(std::vector<Plate*> &answer, std::vector<Plate*> &newPath) {
    std::vector<Plate*> newAnswer;

    if (answer.empty()) {
        std::cout << "path\n";
        answer = newPath;
        return answer;
    }

    for (auto &ap : answer) {
        for (auto &pp : newPath) {
            if (ap->getX() == pp->getX() && ap->getY() == pp->getY())
                newAnswer.push_back(ap);
        }
    }
    return newAnswer;
}*/

int max_row = 0;

// exit plate has coordinates [height - 1; width - 2]
void recursivePath(Plate *plate, std::vector<Plate*> &path, std::vector<Plate*> &answer, Maze* maze){
    path.push_back(plate);
    plate->visit();
    // check if the plate is the exit and if it is, print the path
    if (plate->getX() == maze->getWidth() - 2 && plate->getY() == maze->getHeight() - 1) {

        for (auto &p : path)
            p->setInOriginalRoad(true);

        if (answer.empty()) {
            answer = path;
            abortion = true;
        }
    }

    for (auto &n : plate->getNeighbors()) {
        // if the neighbor is unvisited, visit it
        if (abortion) return;
        if (!n->isVisited() && n->isRoad())
            recursivePath(n, path, answer, maze);
    }

    plate->unvisit();
    path.pop_back();
}

bool tryFindPlateFromOriginalPath(Plate *plate, std::vector<Plate*> &path, std::vector<Plate*> &answer, Maze* maze){
    path.push_back(plate);
    plate->visit();

    if (path.size() != 1) {
        // check if the plate is the exit and if it is, print the path
        if (plate->isInOriginalPath()/* && plate->getX() != 1 && plate->getY() > 2*/) {
            answer = path;
            abortion = true;
            return true;
        }
    }

    for (auto &n : plate->getNeighbors()) {
        // if the neighbor is unvisited, visit it
        if (abortion) return true;

        if (!n->isVisited() && n->isRoad())
            return tryFindPlateFromOriginalPath(n, path, answer, maze);
    }

    plate->unvisit();
    path.pop_back();
    return false;
}

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<Plate*> absoluteAnswer;
    Maze * maze;

    try {
        maze = createMaze();
    } catch (std::domain_error &err) {
        return 1;
    }

    Plate*** plates = maze->getPlates();
    Plate * start = maze->getPlates()[0][1];
    std::vector<Plate*> answer;
    std::vector<Plate*> path;

    // add neighbors to all plates
    for (int i = 0; i < maze->getHeight(); i++) {
        for (int j = 0; j < maze->getWidth(); j++) {
            maze->getPlates()[i][j]->addNeighbors(maze->getPlates(), maze->getWidth(), maze->getHeight());
        }
    }


    recursivePath(maze->getPlates()[0][1], path, answer, maze);


    if (answer.empty()) {
        std::cerr << "Error: Cesta neexistuje!\n";
        delete maze;
        return 1;
    }

    for (auto &pp : answer) {
        pp->unvisit();
    }

    std::vector<Plate*> pathBushes;
    std::vector<Plate*> answerBushes;

    for (size_t i = 1; i < answer.size(); ++i) {

        /*for (size_t k = i; k > 0; --k) {
            if (answer[k]->isRoad()) {
                start = answer[k];
                break;
            }
        }*/

        pathBushes.clear();
        answerBushes.clear();


        answer[i]->unroad();

        bool found = tryFindPlateFromOriginalPath(answer[i-1], pathBushes, answerBushes, maze);

        abortion = false;

        if (!found) {
            absoluteAnswer.push_back(answer[i]);
            answer[i]->roadate();
        }

        for (auto &pl : pathBushes)
            pl->unvisit();

        for (auto &pl : answerBushes)
            pl->unvisit();
    }

    for (auto &pp : answer) {
        pp->roadate();
    }

    printPlate(maze, absoluteAnswer);

    delete maze;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds >(end - begin).count() << "[ms]" << std::endl;
    return 0;
}

