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

#include "Renderer.h"
#include "Building.h"
#include "Road.h"
#include "Entity.h"

template <class T>
using Vector2D = std::vector< std::vector<T> >;

enum Phase {
    ZombieMove, ZombieInfect, PeopleMove
};

class Town {
public:
    // Singleton instance
    static Town* Instance();

    // The current time in fictoseconds (A unit of time that makes sense)
    int time = 0;
    int frame = Renderer::timestep;
    Phase phase = PeopleMove;

    void update(Renderer* renderer, float deltaTime);

    // Add a building or road to the town, invalid if finishCreate() has been called.
    void addBuilding(Building* building);
    void addRoad(Road* road);
    void addEntity(Entity* entity);

    // Data encapsulation - can only read buildings, roads and entities for rendering
    std::vector<Building*> getBuildings();
    std::vector<Road*> getRoads();
    std::vector<Entity*> getEntities();

    std::vector<int>* adjList;

    // Finshed building town, create adjacency matrix
    void finishCreate();

    Vector2 townCentre;

    int getAdjacencyMatrixCell(int x, int y);
    void printAdjacencyMatrix();

    // Deconstructor
    ~Town();

private:
    Town();
    static Town* singletonInstance;

    // Private array to store buildings and roads
    std::vector<Building*> buildings;
    std::vector<Road*> roads;
    std::vector<Entity*> entities;

    void zombieMove(Renderer* renderer);
    void zombieInfect(Renderer* renderer);
    void peopleMove(Renderer* renderer);
    

    bool finished = false;

    // Unitialisised pointer to adjacency matrix
    int* adjMat;
};

#endif // __TOWN_H_INCLUDED__
