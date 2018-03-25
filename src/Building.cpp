/*******************************************************************************************
*
*   Building | Object for modelling buildings in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

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

// Will return true if capacity limit is not reached
bool Building::addEntity(Entity* entity) {
	// Check capcaity
	if (this->entities.size() < this->capacity) {
		// Add entity to building
		this->entities.push_back(entity);
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
	for (int i = 0; i < this->entities.size(); i++) {
		if (this->entities[i] == entity) {
			index = i;
		}
	}
	// If this entity is not in this building
	if (index == -1) {
		return false;
	}

	// If successfully added
	if (building->addEntity(entity)) {
		// Remove from this building
		this->entities.erase(entities.begin()+index);
		return true;
	} else {
		return false;
	}
}

// ID should not be changed
int Building::getID() {
	return this->id;
}

