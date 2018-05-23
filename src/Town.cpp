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
#include <random>
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

// Phases
void Town::zombieMove(Renderer* renderer) {
    for (Entity* entity : entities) {
        if (entity->zombie) {
            Building* oldBuilding = entity->building;
            int building = oldBuilding->getID();

            // Choose building with the highest zombie ratio
            int bestRatio = oldBuilding->zombieRatio();
            Building* nextBuilding = oldBuilding;
            for (int newBuilding : adjList[building]) {
                if (buildings[newBuilding]->zombieRatio() > bestRatio) {
                    bestRatio = buildings[newBuilding]->zombieRatio();
                    nextBuilding = buildings[newBuilding];
                }
            }

            if (entity->building->moveEntityTo(entity, nextBuilding)) {
                renderer->moveEntityBetween(oldBuilding, nextBuilding, entity->zombie);
            }
        }
    }
}
void Town::zombieInfect(Renderer* renderer) {
    // Each zombie infects 1 person in their building
    std::vector<Entity*> toInfect;
    for (Entity* entity : entities) {
        if (entity->zombie) {
            Building* building = entity->building;
            for (Entity* person : building->entities) {
                if (!person->zombie) {
                    toInfect.push_back(person);
                    building->numZombies++;
                    building->numPeople--;
                    break;
                }
            }
        }
    }
    for (Entity* infected : toInfect) {
        infected->zombie = true;
    }
}
void Town::peopleMove(Renderer* renderer) {
    for (Entity* entity : entities) {
        if (!entity->zombie) {
            Building* oldBuilding = entity->building;

            int building = oldBuilding->getID();

            // Choose building with fewest zombies
            int bestZombies = oldBuilding->numZombies;
            Building* nextBuilding = oldBuilding;
            for (int newBuilding : adjList[building]) {
                if (buildings[newBuilding]->numZombies <= bestZombies) {
                    bestZombies = buildings[newBuilding]->numZombies;
                    nextBuilding = buildings[newBuilding];
                }
            }

            if (entity->building->moveEntityTo(entity, nextBuilding)) {
                renderer->moveEntityBetween(oldBuilding, nextBuilding, entity->zombie);
            }
        }
    }
}

// This function will be used to update building and road values, and call corresponding entity update functions
void Town::update(Renderer* renderer, float deltaTime) {
    // Run every timestep
    if (frame == Renderer::timestep) {
        frame = 0;
        time++;

        switch (phase) {
        case PeopleMove:
            zombieMove(renderer);
            phase = ZombieMove;
            break;
        case ZombieMove:
            zombieInfect(renderer);
            phase = ZombieInfect;
            break;
        case ZombieInfect:
            peopleMove(renderer);
            phase = PeopleMove;
            break;
        }
    }

    frame++;
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

void Town::addEntity(Entity* entity) {
    entities.push_back(entity);
}

// Return private properties
const std::vector<Building*>& Town::getBuildings() {
    return this->buildings;
}
const std::vector<Road*>& Town::getRoads() {
    return this->roads;
}
const std::vector<Entity*>& Town::getEntities() {
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
    
    // Create adjacency list
    adjList = new std::vector<int>[numBuildings];

    // Register edge connections
    for (Road* road : this->roads) {
        // ID of building corresponds to index of adjacency matrix
        int b1 = road->building1->getID();
        int b2 = road->building2->getID();
        int length = road->length();
        
        // Bi-directional matrix, transpose is identical
        this->adjMat[index(b1, b2, numBuildings)] = length;
        this->adjMat[index(b2, b1, numBuildings)] = length;

        adjList[b1].push_back(b2);
        adjList[b2].push_back(b1);
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
