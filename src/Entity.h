/*******************************************************************************************
*
*   Entity | Humans and zombies
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include <string>
#include <vector>

#include "Weapon.h"

class Building;

class Entity {
public:
    Entity(std::string name);

    std::string name;
    // Entity starts off as not a zombie
    bool zombie = false;

  	// Has not been added to building yet
    Building* building;

    // Default starting stats

    // Speed and strength will decrease as hunger increases
    int strength = 10;
    int speed = 10;
    // Hunger will increase with time and deplete building resources
    int hunger = 0;
    // No default weapons
    std::vector<Weapon*> weapons;

    /*
     * This pathfinding algorithm will use a priority queue for Dijkstra's
     */
    void findNextPath();
    

private:

    
};

#endif // __ENTITY_H_INCLUDED__
