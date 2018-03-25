/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <string>
#include <iostream>
#include <raylib.h>

#include "Town.h"
#include "GroundZeroRenderer.h"

GroundZeroRenderer::GroundZeroRenderer() {
    InitWindow(this->width, this->height, (void*)"Ground Zero");
    SetTargetFPS(120);
}
GroundZeroRenderer::~GroundZeroRenderer() {  
    CloseWindow();        // Close window and OpenGL context
}

void GroundZeroRenderer::drawRoad(Road* road) {

    Vector2 position;
    Vector2 linePosition;
    Vector2 size;
    Vector2 lineSize;

    // Width of dividing line
    float lineWidth = 3;

    // Change properties based on orientation
    if (road->northsouth) {
        // Convert position of road (centre) to raylib compatable (top left corner)
        position = {
            road->position.x - road->width/2,
            road->position.y - road->length/2,
        };
        linePosition = {
            road->position.x - lineWidth/2,
            road->position.y - road->length/2,
        };

        size = {road->width, road->length};
        lineSize = {lineWidth, road->length};
    } else {
        position = {
            road->position.x - road->length/2,
            road->position.y - road->width/2,
        };
        linePosition = {
            road->position.x - road->length/2,
            road->position.y - lineWidth/2,
        };

        size = {road->length, road->width};
        lineSize = {road->length, lineWidth};
    }

    // Draw rectangle of road, with converted position, size and colour
    DrawRectangleV(position, size, BLACK);
    DrawRectangleV(linePosition, lineSize, WHITE);
}


void GroundZeroRenderer::drawBuilding(Building* building) {
    // Convert position of building (centre) to raylib compatable (top left corner)
    Vector2 position = {
        building->position.x - building->size.x/2,
        building->position.y - building->size.y/2,
    };
    // Draw rectangle of building, with converted position, size and colour
    DrawRectangleV(position, building->size, building->colour);

    // DRAW BUILDING TEXT
    int fontSize = 16;
    Color fontColour = BLACK;
    int textWidth = MeasureText(building->name.c_str(), fontSize);

    // Draw building name (Font size 16)
    DrawText(building->name.c_str(), building->position.x-textWidth/2, position.y, fontSize, fontColour);
    
    // Draw building stats (capacity, defensibility and resources)
    DrawText(std::to_string(building->capacity).c_str(), 
        position.x+5, position.y+15, fontSize, fontColour);
    
    DrawText(std::to_string(building->defensibility).c_str(), 
        position.x+5, position.y+30, fontSize, fontColour);
    
    DrawText(std::to_string(building->resources).c_str(), 
        position.x+5, position.y+45, fontSize, fontColour);
}

// RENDER TOWN, run every frame
void GroundZeroRenderer::render(float deltaTime) {
    // Start drawing context
    BeginDrawing();
    // Clear the last frame
    ClearBackground(this->backgroundColour);

    // If show FPS is on, draw the FPS
    if (this->showFPS) {
        int fps = 0; // deltaTime is in seconds
        if (deltaTime > 0)
            fps = (1.0/deltaTime + 0.5); // Round to nearest FPS rather than truncate
        // Draw in top left corner in red text
        std::string text = std::to_string(fps) + " FPS";
        DrawText(text.c_str(), 15, 15, 30, RED);
    }

    // Draw roads as edges first
    for (Road* road : Town::Instance()->roads) {
        this->drawRoad(road);
    }

    // Draw all the buildings as nodes second
    for (Building* building : Town::Instance()->buildings) {
        this->drawBuilding(building);
    }

    EndDrawing();
}

void GroundZeroRenderer::mainloop() {
    while (!WindowShouldClose()) {    // Detect window close button or ESC key

        // Time in milliseconds since last frame
        float dt = GetFrameTime();

        // Update town time
        Town::Instance()->update(this, dt);
        // Render town
        this->render(dt);
    }
}