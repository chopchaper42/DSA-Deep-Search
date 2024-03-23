//
// Created by greg on 13.3.24.
//

#include <vector>

#ifndef DEEP_SEARCH_PLATE_H
#define DEEP_SEARCH_PLATE_H


class Plate {
public:
    Plate(int x, int y, bool road);
    ~Plate() {
    }
    Plate();
    void addNeighbor(Plate *plate);
    void addNeighbors(Plate*** plates, int width, int height);
    std::vector<Plate*> getNeighbors();
    void printCoordinatesAndNeighborsNumber();
    int getX();
    int getY();
    Plate* getPreviousPlate();
    bool isRoad() { return road; }
    bool isVisited() { return visited; }
    void visit() { visited = true; }
    void unvisit() { visited = false; }

private:
    int x;
    int y;
    bool road = false;
    bool visited = false;
    std::vector<Plate*> neighbors;
};


#endif //DEEP_SEARCH_PLATE_H
