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

int main() {
    int screenWidth, screenHeight;
    getScreenResolution(screenWidth, screenHeight);

    GroundZeroRenderer* renderer = new GroundZeroRenderer();

    // SETUP TOWN ---------------------------------------------------------------
    Town* town = Town::Instance();
    
    // Building has parameters:      Name      Capacity  Defensibility  Resources
    Building* b1 = new Building("Minas Morgul",   10,         60,          5);
    b1->position = {190, 200};
    b1->size = {350, 150};
    town->addBuilding(b1);

    // MAIN LOOP ----------------------------------------------------------------
    renderer->mainloop();


    // CLEANUP ------------------------------------------------------------------
    delete renderer;
    delete town;

    return 0;
}