/*******************************************************************************************
*
*   Road | Object for modelling roads in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <utility>

#include "Road.h"
#include "Building.h"

Road::Road(int width, int length, Building* b1, Building* b2) {
	this->width = width;
	this->length = length;
	this->building1 = b1;
	this->building2 = b2;
}

std::pair<Building*, Building*> Road::getConnectedBuildings() {
	return {this->building1, this->building2};
}

