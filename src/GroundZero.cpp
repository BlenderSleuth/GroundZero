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

#include "Game.h"
#include "GroundZeroRenderer.h"

struct Layers {
    static const int TEXT = 40;
};

void getScreenResolution(int &width, int &height) {
    glfwInit();
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
}

// Run every frame
void runfunc(GroundZeroRenderer* renderer) {
    ClearBackground(RAYWHITE);
    int x = 190, y = 200;
    renderer->relPos(x, y);
    DrawText("Congrats! You created your first window!", x, y, 20, LIGHTGRAY);
}

int main() {
    int screenWidth, screenHeight;
    getScreenResolution(screenWidth, screenHeight);
    Game::Instance()->scale = screenWidth / Game::Instance()->width();

    GroundZeroRenderer* renderer = new GroundZeroRenderer();

    // SETUP TOWN ---------------------------------------------------------------


    // MAIN LOOP ----------------------------------------------------------------
    renderer->mainloop(&runfunc);


    // CLEANUP ------------------------------------------------------------------
    delete renderer;

    return 0;
}