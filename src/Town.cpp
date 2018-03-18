/*******************************************************************************************
*
*   Town | Global state data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

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
    
    singletonInstance = nullptr;
}

Town* Town::Instance() {
    if (!singletonInstance)
        singletonInstance = new Town;
    return singletonInstance;
}
void Town::update(GroundZeroRenderer* renderer, int deltaTime) {
    
}

void Town::addBuilding(Building* building) {
    this->buildings.push_back(building);
}
void Town::addRoad(Road* road) {
    this->roads.push_back(road);
}