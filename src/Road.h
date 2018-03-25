/*******************************************************************************************
*
*   Road | Object for modelling roads in our town
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __ROAD_H_INCLUDED__
#define __ROAD_H_INCLUDED__

#include <utility>
#include <raylib.h>

class Building;

class Road {
public:
	Road(int width, int length, Building* b1, Building* b2);

	float length = 0, width = 0;
	bool northsouth = true;
	Vector2 position = {0, 0};

	std::pair<Building*, Building*> getConnectedBuildings();

private:
	Building* building1;
	Building* building2;
    
};

#endif
