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
    if (numZombies == 0) {
        return std::max((double)numPeople, 0.5);
    } else {
        return ((double)numPeople) / ((double)numZombies);
    }
}

// Will return true if capacity limit is not reached
bool Building::addEntity(Entity* entity) {
    // Check capacity
    if (numPeople < capacity || entity->zombie) {
        // Add entity to building
        entities.push_back(entity);
        if (entity->zombie) { numZombies++; } else { numPeople++; }
        entity->building = this;

        return true;
    } else {
        return false;
    }
}

// Will return true if entity has successfully moved
bool Building::moveEntityTo(Entity* entity, Building* building) {
    // Find entity in this building entity list:
    int index = -1;
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i] == entity) {
            index = i;
            break;
        }
    }
    // If this entity is not in this building
    if (index == -1) {
        return false;
    }

    // If successfully added
    if (building->addEntity(entity)) {
        // Remove from this building
        entities.erase(entities.begin()+index);
        if (entity->zombie) { numZombies--; } else { numPeople--; }
        
        return true;
    } else {
        return false;
    }
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

// ID should not be changed
int Building::getID() {
    return id;
}

