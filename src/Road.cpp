/*******************************************************************************************
*
*   Road | Object for modelling roads in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <utility>
#include <cmath>

#include "Road.h"
#include "Building.h"

Road::Road(int width, Building* b1, Building* b2) {
    this->width = width;
    this->building1 = b1;
    this->building2 = b2;
}

// Returns both buildings that this road connects
std::pair<Building*, Building*> Road::getConnectedBuildings() {
    return {this->building1, this->building2};
}

int Road::length() {
    // Rough integer length of road using standard Pythag
    float x = this->building1->position.x - this->building2->position.x;
    float y = this->building1->position.y - this->building2->position.y;
    return floor(sqrt(pow(x, 2) + pow(y, 2)));
}

