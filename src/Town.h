/*******************************************************************************************
*
*   Town | Global state data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __TOWN_H_INCLUDED__
#define __TOWN_H_INCLUDED__

#include <vector>

#include "GroundZeroRenderer.h"
#include "Building.h"
#include "Road.h"

template <class T>
using Vector2D = std::vector< std::vector<T> >;

class Town {
public:
    static Town* Instance();
    int time = 0;

    void update(GroundZeroRenderer* renderer, float deltaTime);

    void addBuilding(Building* building);
    void addRoad(Road* road);

    Vector2D<int> adjList;

    std::vector<Building*> buildings;
    std::vector<Road*> roads;

    ~Town();

private:
    Town();
    static Town* singletonInstance;
};

#endif
