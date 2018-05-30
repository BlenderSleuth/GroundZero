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
#include <random>
#include <raylib.h>

#include "Renderer.h"
#include "Town.h"
#include "Building.h"
#include "Road.h"


void createTown(Town* town) {
    // TOWN COODINATES: 
    // Origin (0, 0) is top right
    // Width and height are mapped 0 - 1000 to actual screen resolution
    // Building position is from centre

    // Building has parameters:             Name      Capacity  Defensibility  Resources
    Building* townCentre = new Building("Town Centre",   50,         10,           5);
    // Position in the middle on the top
    townCentre->position = {500, 100};
    townCentre->size = {110, 100};
    townCentre->colour = RAYWHITE;
    town->addBuilding(townCentre);

    // Building has parameters:             Name      Capacity  Defensibility  Resources
    Building* shopPlaza = new Building("Shop Plaza",    30,         20,           50);
    shopPlaza->position = {500, 600};
    shopPlaza->size = {150, 100};
    shopPlaza->colour = WHITE;
    town->addBuilding(shopPlaza);

    // Road has parameters:   width   from         to
    Road* mainStreet = new Road(50, townCentre, shopPlaza);
    town->addRoad(mainStreet);

    // Building has parameters:                 Name         Capacity  Defensibility  Resources
    Building* hardwareStore = new Building("Hardware Store",    20,         80,           10);
    hardwareStore->position = {850, 125};
    hardwareStore->size = {150, 150};
    hardwareStore->colour = LIGHTGRAY;
    town->addBuilding(hardwareStore);

    // Road has parameters:  width   from         to
    Road* road1 = new Road(    40, townCentre, hardwareStore);
    town->addRoad(road1);

    // Building has parameters:              Name                 Capacity  Defensibility  Resources
    Building* auntieDot = new Building("Auntie Dot's Steakhouse",     10,         80,           30);
    auntieDot->position = {850, 400};
    auntieDot->size = {200, 75};
    auntieDot->colour = SKYBLUE;
    town->addBuilding(auntieDot);

    // Road has parameters:  width  from         to
    Road* road2 = new Road(   40, auntieDot, hardwareStore);
    town->addRoad(road2);

    // Building has parameters:        Name               Capacity  Defensibility  Resources
    Building* grandma = new Building("Grandma's Bakery",     5,         20,           50);
    grandma->position = {850, 600};
    grandma->size = {150, 100};
    grandma->colour = GOLD;
    town->addBuilding(grandma);

    // Road has parameters:  width  from       to
    Road* road3 = new Road(   20, grandma, auntieDot);
    town->addRoad(road3);

    // Building has parameters:        Name            Capacity  Defensibility  Resources
    Building* barney = new Building("Barney's Joint",     14,         10,           10);
    barney->position = {900, 830};
    barney->size = {140, 100};
    barney->colour = VIOLET;
    town->addBuilding(barney);

    // Road has parameters:  width    from    to
    Road* road4 = new Road(   10,    barney, grandma);
    town->addRoad(road4);

    // Building has parameters:        Name            Capacity  Defensibility  Resources
    Building* bobjones = new Building("Ol' Bob Jones'",     5,         3,           20);
    bobjones->position = {620, 400};
    bobjones->size = {120, 100};
    bobjones->colour = BEIGE;
    town->addBuilding(bobjones);

    // Road has parameters:  width    from    to
    Road* road5 = new Road(   30,    bobjones, grandma);
    town->addRoad(road5);

    // Road has parameters:  width    from        to
    Road* road6 = new Road(   20,   townCentre, bobjones);
    town->addRoad(road6);

    // Building has parameters:       Name      Capacity  Defensibility  Resources
    Building* bigal = new Building("Big Al's",     30,         60,           15);
    bigal->position = {680, 630};
    bigal->size = {140, 150};
    bigal->colour = YELLOW;
    town->addBuilding(bigal);

    // Road has parameters:  width    from    to
    Road* road7 = new Road(   30,    bigal,  bobjones);
    town->addRoad(road7);

    // Building has parameters:       Name      Capacity  Defensibility  Resources
    Building* woolies = new Building("Woolies",     100,         70,           600);
    woolies->position = {500, 840};
    woolies->size = {230, 200};
    woolies->colour = GREEN;
    town->addBuilding(woolies);

    // Road has parameters:  width     from      to
    Road* road8 = new Road(   80,    woolies, shopPlaza);
    town->addRoad(road8);

    //Building has parameters:         Name       Capacity   Defensibility  Resources
    Building* minas = new Building("Minas Morgul",   10,          80,          0);
    minas->position = {120, 100};
    minas->size = {130, 120};
    minas->colour = DARKGRAY;
    town->addBuilding(minas);

    // Road has parameters:  width      from      to
    Road* road9 = new Road(   10,    minas, townCentre);
    town->addRoad(road9);

    //Building has parameters:         Name         Capacity   Defensibility  Resources
    Building* snazzyjoe = new Building("Snazzy Joe",   4,          4,          15);
    snazzyjoe->position = {140, 300};
    snazzyjoe->size = {130, 100};
    snazzyjoe->colour = PURPLE;
    town->addBuilding(snazzyjoe);

    // Road has parameters:  width   from      to
    Road* road10 = new Road(  15,   snazzyjoe, minas);
    town->addRoad(road10);

    //Building has parameters:        Name     Capacity   Defensibility  Resources
    Building* dankmo = new Building("Dank Mo's",   10,          40,          30);
    dankmo->position = {120, 450};
    dankmo->size = {130, 100};
    dankmo->colour = LIME;
    town->addBuilding(dankmo);

    // Road has parameters:  width   from      to
    Road* road11 = new Road(  30,   dankmo, snazzyjoe);
    town->addRoad(road11);

    // Road has parameters:  width   from      to
    Road* road12 = new Road(  20,   dankmo, shopPlaza);
    town->addRoad(road12);

    //Building has parameters:               Name            Capacity   Defensibility  Resources
    Building* dodgydave = new Building("Dodgy Dave's Used Cars",   15,          2,          20);
    dodgydave->position = {340, 300};
    dodgydave->size = {200, 120};
    dodgydave->colour = ORANGE;
    town->addBuilding(dodgydave);

    // Road has parameters:  width   from      to
    Road* road13 = new Road(  10,   dodgydave, shopPlaza);
    town->addRoad(road13);

    // Road has parameters:  width   from      to
    Road* road14 = new Road(  15,   dodgydave, snazzyjoe);
    town->addRoad(road14);

    //Building has parameters:                   Name               Capacity   Defensibility  Resources
    Building* bigmac = new Building("Big Mac Special Sauce Factory",   50,          10,          40);
    bigmac->position = {160, 750};
    bigmac->size = {250, 200};
    bigmac->colour = YELLOW;
    town->addBuilding(bigmac);

    // Road has parameters:  width   from      to
    Road* road15 = new Road(  20,   bigmac, dankmo);
    town->addRoad(road15);

    // Set town centre (for position)
    town->townCentre = {500, 500};

    int NUM_PEOPLE = 100;

    // Random number generator
    std::random_device rd;
    std::mt19937 rng(rd()); 
    std::uniform_int_distribution<int> uni(0, town->getBuildings().size()-1);

    // Randomly place people inside the town
    for (int i = 0; i < NUM_PEOPLE; i++) {
        Entity* resident = new Entity();
        int building = uni(rng);
        if (town->getBuildings()[building]->addEntity(resident)) {
            town->addEntity(resident);
        } else {
            delete resident;
        }
    }

    // Create zombie at town centre
    Entity* zombie = new Entity();
    zombie->zombie = true;
    townCentre->addEntity(zombie);
    town->addEntity(zombie);

    // Signal that we have finished building the town.
    town->finishCreate();
}

int main() {
    // SETUP TOWN ---------------------------------------------------------------
    Town* town = Town::Instance();
    createTown(town);

    // Renderer object controls how objects look
    Renderer* renderer = new Renderer();

    // MAIN LOOP ----------------------------------------------------------------
    renderer->mainloop(); // Render and simulate Town

    // CLEANUP ------------------------------------------------------------------
    delete renderer; // This will call the renderer deconstructor, to close the windows and delete game resources
    delete town; // This will call the town deconstructor, which deletes the buildings, roads, and entities.

    return 0;
}
