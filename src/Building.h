/*******************************************************************************************
*
*   Building | Object for modelling buildings in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __BUILDING_H_INCLUDED__
#define __BUILDING_H_INCLUDED__

#include <string>
#include <raylib.h>
#include "Point.h"

class Building {
public:
	Building(std::string name, int capacity, int defensibility, int resources);

	int capacity, defensibility, resources;
	std::string name;

	Vector2 position = {0, 0};
	Vector2 size = {1, 1};

private:
	
    
};

#endif
