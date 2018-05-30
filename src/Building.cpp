/*******************************************************************************************
*
*   Building | Object for modelling buildings in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <algorithm>
#include <string>
#include <iostream>

#include "Town.h"
#include "Road.h"
#include "Building.h"
#include "Entity.h"

// As buildings are created, the ID is used as an index in the adjacency matrix
int currentID = 0;

Building::Building(std::string name, int capacity, int defensibility, int resources) {
    this->name = name;
    this->capacity = capacity;
    this->defensibility = defensibility;
    this->resources = resources;
    this->id = currentID++;
}

double Building::zombieRatio() {
    if (zombies.size() == 0) {
        return std::max((double)people.size(), 0.5);
    } else {
        return ((double)people.size()) / ((double)zombies.size());
    }
}

// Will return true if capacity limit is not reached
bool Building::addEntity(Entity* entity) {
    if (entity->zombie) {
        // Add zombie to building
        zombies.insert(entity);
        visNumZombies++;
        entity->building = this;
        return true;

        // Check capacity
    } else if (people.size() < capacity) {
        // Add person to building
        people.insert(entity);
        visNumPeople++;
        entity->building = this;

        return true;
    } 

    return false;
}

// Will return true if entity has successfully moved
bool Building::moveEntityTo(Entity* entity, Building* building) {
    if (building == this) {
        return false;
    }

    // Find entity in this building entity list:
    if (entity->zombie) {
        auto index = zombies.find(entity);

        // If this zombie is not in this building
        if (index == zombies.end()) {
            return false;
        }

        // If successfully added
        if (building->addEntity(entity)) {
            // Remove from this building
            zombies.erase(index);
            visNumZombies--;
            return true;
        } else {
            return false;
        }
    } else {
        auto index = people.find(entity);

        // If this person is not in this building
        if (index == people.end()) {
            return false;
        }
        // If successfully added
        if (building->addEntity(entity)) {
            // Remove from this building
            people.erase(index);
            visNumPeople--;
            return true;
        } else {
            return false;
        }
    }
}

void Building::makeZombie(Entity* entity) {
    // If this entity does not exist
    if (people.find(entity) == people.end()) {
        return;
    }
    people.erase(entity);
    visNumPeople--;
    entity->zombie = true;
    zombies.insert(entity);
    visNumZombies++;
}

Rectangle Building::boundingBox() {
    return (Rectangle){(int)(position.x - size.x/2), (int)(position.y - size.y/2), (int)size.x, (int)size.y};
}

void Building::highlight() {
    if (!highlighted) {
        highlighted = true;
        originalColour = colour;
        colour = BLUE;
    }
}
void Building::dehighlight() {
    if (highlighted) {
        highlighted = false;
        colour = originalColour;
    }
}

// Return private properties
const std::unordered_set<Entity*>& Building::getPeople() {
    return this->people;
}
const std::unordered_set<Entity*>& Building::getZombies() {
    return this->zombies;
}

int Building::numPeople() {
    return this->visNumPeople;
}
int Building::numZombies() {
    return this->visNumZombies;
}

// ID should not be changed
int Building::getID() {
    return id;
}

