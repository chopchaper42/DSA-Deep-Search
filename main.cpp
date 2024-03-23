#include <iostream>
#include "maze.h"
#include "Plate.h"
#include <stack>

void printVec(std::vector<Plate*> &vec) {
    for (auto &p : vec) {
        std::cout << '[' << p->getX() << ", " << p->getY() << "] ";
    }
    std::cout << '\n';
}

void printPlate(Maze* maze, std::vector<Plate*> &answer) {
//    std::cout << "- - - - - - - - - - -\n";
    for (int i = 0; i < maze->getHeight(); i++) {
        for (int j = 0; j < maze->getWidth(); j++) {
//            std::cout << maze->getPlates()[i][j].getNeighbors().size() << " ";
            Plate *p = maze->getPlates()[i][j];
            char c = '.';

            if (!p->isRoad())
                c = '#';

            for (auto plate : answer) {
                if (plate->getX() == p->getX() && plate->getY() == p->getY()) {
                    c = '!';
                    break;
                }
            }

            std::cout << c << ' ';

        }
        std::cout << '\n';
    }
}

std::vector<Plate*> intersect(std::vector<Plate*> &answer, std::vector<Plate*> &newPath) {
    std::vector<Plate*> newAnswer;

    if (answer.empty()) {
        answer = newPath;
        return answer;
    }

    for (auto &ap : answer) {
        for (auto &pp : newPath) {
            if (ap->getX() == pp->getX() && ap->getY() == pp->getY())
                newAnswer.push_back(ap);
        }
    }

    /*for (int i = 0; i < answer.size(); ++i) {
        if (answer[i]->getX() == newPath[i]->getX() && answer[i]->getY() == newPath[i]->getY())
            newAnswer.push_back(answer[i]);
    }*/
    return newAnswer;
}


// exit plate has coordinates [height - 1; width - 2]
void recursivePath(Plate *plate, std::vector<Plate*> &path, std::vector<Plate*> &answer, Maze* maze){
    path.push_back(plate);
//    printVec(path);
    // add the plate to the path
    plate->visit();

    // check if the plate is the exit and if it is, print the path
    if (plate->getX() == maze->getWidth() - 2 && plate->getY() == maze->getHeight() - 1) {

        if (answer.empty()) {
            // set path as the answer
            answer = path;
//            std::cout << "The first path: \n";
//            printPlate(maze, answer);

        } else {
            // print the path
            /*std::cout << "Path: \n";
            printPlate(maze, path);*/

            // print the intersection
            answer = intersect(answer, path);

//            std::cout << "INTERSECTION PERFORMED: \n";
//            printPlate(maze, answer);
        }

        // unvisit all nodes
        /*for (auto &p : path) {
            p->unvisit();
        }
        // erase the path
        path.clear();
        return;*/
    }

    /*for (auto n : plate->getNeighbors())
        if (n != plate->getPreviousPlate()) {
            n->setPrevious(plate);
            recursivePath(n, path, answer, maze);
        }*/

    bool unvisitedRemain = false;
    for (auto &n : plate->getNeighbors())
        if (!n->isVisited()) {
            unvisitedRemain = true;
            break;
        }


    for (auto &n : plate->getNeighbors()) {
        // if the neighbor is unvisited, visit it
        if (!n->isVisited())
            recursivePath(n, path, answer, maze);


    }

//    if (!unvisitedRemain) {
        plate->unvisit();
        path.pop_back();
//    }
}

int main() {
    // call the algorithm
    Maze * maze;
    try {
        maze = createMaze();
    } catch (std::domain_error err) {
        return 1;
    }

    std::stack<Plate*> toVisit;

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
        std::cerr << "Error: Cesta neexistuje!";
        return 1;
    }

    printPlate(maze, answer);
//    printPlate(maze, answer);

    delete maze;
    return 0;
}

