/*******************************************************************************************
*
*   Entity | Humans and zombies
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <string>

#include "Building.h"
#include "Entity.h"

Entity::Entity(std::string name) {
    this->name = name;
}

void Entity::findNextPath() {
    // Nothing here yet...
}

