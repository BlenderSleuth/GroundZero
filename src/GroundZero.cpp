/*******************************************************************************************
*
*   Ground Zero | Town data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <iostream>
#include <utility>
#include <tuple>
#include <raylib.h>
#include <GLFW/glfw3.h>

#include "GroundZeroRenderer.h"
#include "Town.h"
#include "Building.h"
#include "Road.h"


struct Layers {
    static const int TEXT = 40;
};

void getScreenResolution(int &width, int &height) {
    glfwInit();
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
}

void createTown(Town* town) {
    // TOWN COODINATES: 
    // Origin (0, 0) is top right
    // Width and height are mapped 0 - 1000 to actual screen resolution
    // Building position is from centre

    // Building has parameters:      Name      Capacity   Defensibility  Resources
    // Building* b1 = new Building("Minas Morgul",   10,          60,          5);
    // b1->position = {190, 200};
    // b1->size = {350, 150};
    // town->addBuilding(b1);

    // Building has parameters:             Name      Capacity  Defensibility  Resources
    Building* townCentre = new Building("Town Centre",   50,         10,           5);
    // Position in the middle on the top
    townCentre->position = {500, 100};
    townCentre->size = {100, 100};
    townCentre->colour = RAYWHITE;
    town->addBuilding(townCentre);

    // Building has parameters:             Name      Capacity  Defensibility  Resources
    Building* shopPlaza = new Building("Shop Plaza",    30,         20,           50);
    shopPlaza->position = {500, 800};
    shopPlaza->size = {150, 100};
    shopPlaza->colour = WHITE;
    town->addBuilding(shopPlaza);

    // Road has parameters:   width  length    from         to
    Road* mainStreet = new Road(50,   700, townCentre, shopPlaza);
    // Set the position to the middle, below town centre
    mainStreet->position = {500, 400};
    mainStreet->northsouth = true;
    town->addRoad(mainStreet);

    // Building has parameters:                 Name         Capacity  Defensibility  Resources
    Building* hardwareStore = new Building("Hardware Store",    20,         80,           10);
    hardwareStore->position = {800, 150};
    hardwareStore->size = {200, 200};
    hardwareStore->colour = LIGHTGRAY;
    town->addBuilding(hardwareStore);

    // Road has parameters:  width  length   from         to
    Road* road1 = new Road(40,    200, townCentre, hardwareStore);
    road1->position = {650, 100};
    road1->northsouth = false;
    town->addRoad(road1);

    // Building has parameters:             Name       Capacity  Defensibility  Resources
    Building* auntieDot = new Building("Auntie Dot's",     3,         80,           30);
    auntieDot->position = {800, 300};
    auntieDot->size = {100, 75};
    auntieDot->colour = SKYBLUE;
    town->addBuilding(auntieDot);

    // Road has parameters:  width  length      from         to
    Road* road2 = new Road(40,    150, auntieDot, hardwareStore);
    road2->position = {800, 225};
    road2->northsouth = true;
    town->addRoad(road2);
}

int main() {
    int screenWidth, screenHeight;
    getScreenResolution(screenWidth, screenHeight);

    GroundZeroRenderer* renderer = new GroundZeroRenderer();

    // SETUP TOWN ---------------------------------------------------------------
    Town* town = Town::Instance();
    createTown(town);

    // MAIN LOOP ----------------------------------------------------------------
    renderer->mainloop(); // Render and simulate Town


    // CLEANUP ------------------------------------------------------------------
    delete renderer;
    delete town;

    return 0;
}