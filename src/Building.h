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
#include <vector>
#include <set>
#include <raylib.h>

#include "Entity.h"

class Road;

class Building {
public:
    Building(std::string name, int capacity, int defensibility, int resources);

    std::string name;
    int capacity, defensibility, resources;

    Vector2 position = {0, 0};
    Vector2 size = {1, 1};
    
    Color colour = WHITE;
    bool selected = false;
    
    const std::set<Entity*>& getPeople();
    const std::set<Entity*>& getZombies();
    int numZombies();
    int numPeople();

    double zombieRatio();
    
    bool addEntity(Entity* entity);
    bool moveEntityTo(Entity* entity, Building* building);
    void makeZombie(Entity* entity);

    Rectangle boundingBox();

    void highlight();
    void dehighlight();

    int getID();

private:
    Color originalColour;
    bool highlighted;
    int id;

    std::set<Entity*> people;
    std::set<Entity*> zombies;
};

#endif // __BUILDING_H_INCLUDED__
