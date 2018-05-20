/*******************************************************************************************
*
*   Weapon | A transferable battle object between entities and buildings
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __WEAPON_H_INCLUDED__
#define __WEAPON_H_INCLUDED__

#include <string>

enum class WeaponType {
    Flamethrower
};

class Weapon {
public:
    Weapon(WeaponType type);

    WeaponType type;
    
private:
    
};

#endif // __WEAPON_H_INCLUDED__
