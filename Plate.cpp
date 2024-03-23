//
// Created by greg on 13.3.24.
//

#include <iostream>
#include "Plate.h"
#include "maze.h"

Plate::Plate(int x, int y, bool road): x{x}, y{y}, road{road}  {}

void Plate::addNeighbor(Plate *plate) {
    if (plate->road)
        neighbors.push_back(plate);
}

Plate::Plate() {

}

void Plate::addNeighbors(Plate ***plates, int width, int height) {
    if (!road)
        return;

    if (x > 0) {
        // add the plate on the left
        addNeighbor(plates[y][x - 1]);
    }

    if (y < height - 1) {
        // add the plate below
        addNeighbor(plates[y + 1][x]);
    }

    if (x < width - 1) {
        // add the plate on the right
        addNeighbor(plates[y][x + 1]);
    }

    if (y > 0) {
        // add the plate above
        addNeighbor(plates[y - 1][x]);
    }

}

std::vector<Plate*> Plate::getNeighbors() { // TODO: vector affects efficiency?
    return neighbors;
}

void Plate::printCoordinatesAndNeighborsNumber() {
    std::cout << "x: " << x << "; y: " << y << "; Neighbors: " << neighbors.size() << '\n';
}

int Plate::getX() {
    return x;
}

int Plate::getY() {
    return y;
}
