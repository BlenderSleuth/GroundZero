/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <raylib.h>

#include "Town.h"
#include "GroundZeroRenderer.h"

GroundZeroRenderer::GroundZeroRenderer() {
    InitWindow(this->width, this->height, (void*)"Ground Zero");
    SetTargetFPS(60);
}
GroundZeroRenderer::~GroundZeroRenderer() {  
    CloseWindow();        // Close window and OpenGL context
}

void GroundZeroRenderer::drawBuilding(Building* building) {
    DrawRectangleV(building->position, building->size, LIGHTGRAY);
    DrawText(building->name.c_str(), building->position.x+20, building->position.y+40, 45, BLACK);
}

void GroundZeroRenderer::render(int deltaTime) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (this->drawFPS) {
        int fps = 0;
        if (deltaTime > 0)
            fps = (double)(1.0 / deltaTime) * 1000;
        std::string text = std::to_string(fps) + " FPS";
        DrawText(text.c_str(), 15, 15, 30, RED);
    }

    for (Building* building : Town::Instance()->buildings) {
        this->drawBuilding(building);
    }



    EndDrawing();
}

void GroundZeroRenderer::mainloop() {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::milliseconds ms;

    auto lastTime = clock::now();

    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        auto current = clock::now();
        auto deltaTime = current - lastTime;
        int dt = std::chrono::duration_cast<ms>(deltaTime).count();

        Town::Instance()->update(this, dt);
        this->render(dt);

        //std::this_thread::sleep_for(lastTime + timestep - delta_time);

        lastTime = current;
    }
}