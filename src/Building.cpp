/*******************************************************************************************
*
*   Building | Object for modelling buildings in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <string>

#include "Building.h"

Building::Building(std::string name, int capacity, int defensibility, int resources) {
	this->name = name;
	this->capacity = capacity;
	this->defensibility = defensibility;
	this->resources = resources;
}

