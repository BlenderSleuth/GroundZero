/*******************************************************************************************
*
*   Town | Global state data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

#include "Town.h"

Town::Town() {}

Town* Town::singletonInstance = nullptr;

Town::~Town() {
    // Cleanup memory
    for (Building* b : this->buildings) {
        delete b;
    }
    for (Road* r : this->roads) {
        delete r;
    }

    delete[] this->adjMat;
    
    // Reset singleton
    singletonInstance = nullptr;
}

// Using a singleton because we can only have 1 town
Town* Town::Instance() {
    if (!singletonInstance)
        singletonInstance = new Town;
    return singletonInstance;
}

// This function will be used to update building and road values, and call corresponding entity update functions
void Town::update(Renderer* renderer, float deltaTime) {
    // Nothing here yet...
}

// Add a building if the town has not finished building
void Town::addBuilding(Building* building) {
    if (!this->finished) {
        this->buildings.push_back(building);
    } else {
        throw std::runtime_error("Could not add building when town has finished building");
    }
}
// Add a road if the town has not finished building
void Town::addRoad(Road* road) {
    if (!this->finished) {
        this->roads.push_back(road);
    } else {
        throw std::runtime_error("Could not add road when town has finished building");
    }
}

// Return private properties
std::vector<Building*> Town::getBuildings() {
    return this->buildings;
}
std::vector<Road*> Town::getRoads() {
    return this->roads;
}
std::vector<Entity*> Town::getEntities() {
    return this->entities;
}

// Convert [x][y] to actual index
inline size_t index(int x, int y, size_t rowsize) { 
    // Move 'down' y times, (1 row per down), x across
    return rowsize * y + x;
}

// Function should only be called after all buildings and roads have been added
void Town::finishCreate() {
    // Flag town as finished building
    this->finished = true;

    // Find the number of building we have
    int numBuildings = this->buildings.size();
    int arrSize = numBuildings * numBuildings;

    // Initialise adjacency matrix (contiguous block of memory)
    this->adjMat = new int[arrSize];

    // Set to 0
    std::fill(this->adjMat, this->adjMat+arrSize, 0);
    
    // Register edge connections
    for (Road* road : this->roads) {
        // ID of building corresponds to index of adjacency matrix
        int b1 = road->building1->getID();
        int b2 = road->building2->getID();
        int length = road->length();
        // Bi-directional matrix, transpose is identical
        this->adjMat[index(b1, b2, numBuildings)] = length;
        this->adjMat[index(b2, b1, numBuildings)] = length;
    }
}

// Get a specific matrix cell
int Town::getAdjacencyMatrixCell(int x, int y) {
    if (this->finished) {
        return this->adjMat[index(x, y, this->buildings.size())];
    } else {
        throw std::runtime_error("Could not access adjacency matrix when town has not finished building");
    }
}

// Debug testing of the adjacency matrix
void Town::printAdjacencyMatrix() {
    for (int i = 0; i < this->buildings.size(); i++) {
        for (int j = 0; j < this->buildings.size(); j++) {
            std::cerr << std::setw(4) << this->getAdjacencyMatrixCell(i, j) << " ";
        }
        std::cerr << std::endl;
    }
}
