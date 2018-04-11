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
#include "Renderer.h"

Vector2 operator + (Vector2 v1, Vector2 v2) {
    return Vector2({v1.x + v2.x, v1.y + v2.y});
}
void operator += (Vector2 &v1, Vector2 v2) {
    v1 = v1 + v2;
}

Vector2 operator - (Vector2 v1, Vector2 v2) {
    return Vector2({v1.x - v2.x, v1.y - v2.y});
}
void operator -= (Vector2 &v1, Vector2 v2) {
    v1 = v1 - v2;
}


// Setup the renderer
Renderer::Renderer() {
    InitWindow(this->width, this->height, (void*)"Ground Zero");
    SetTargetFPS(80);
}
// Destroy the renderer
Renderer::~Renderer() {  
    CloseWindow();        // Close window and OpenGL context
}

void Renderer::drawRoad(Road* road) {
    // Get start and end position of road - Positions of buildings that it connects to:
    Vector2 start = road->building1->position + worldPosition;
    Vector2 end = road->building2->position + worldPosition;

    // Draw a line with a thickness that represents width, road colour is dark grey:
    DrawLineEx(start, end, road->width, DARKGRAY);
    // Draw a white dividing line:
    DrawLineEx(start, end, 1, WHITE);
}
void Renderer::drawBuilding(Building* building) {
    // Convert position of building (centre) to raylib compatable (top left corner)
    Vector2 position = {
        building->position.x - building->size.x/2,
        building->position.y - building->size.y/2,
    };

    position += worldPosition;

    // Draw rectangle of building, with converted position, size and colour
    DrawRectangleV(position, building->size, building->colour);

    // DRAW BUILDING TEXT
    int fontSize = 16;
    Color fontColour = BLACK;
    int textWidth = MeasureText(building->name.c_str(), fontSize);

    // Draw building name
    DrawText(building->name.c_str(), position.x+building->size.x/2-textWidth/2, position.y+5, fontSize, fontColour);
    
    // Draw building stats (capacity, defensibility and resources)
    DrawText(std::to_string(building->capacity).c_str(), 
        position.x+10, position.y+25, fontSize, fontColour);
    
    DrawText(std::to_string(building->defensibility).c_str(), 
        position.x+10, position.y+40, fontSize, fontColour);
    
    DrawText(std::to_string(building->resources).c_str(), 
        position.x+10, position.y+55, fontSize, fontColour);
}

// RENDER TOWN, run every frame
void Renderer::render(float deltaTime) {
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
        DrawText(text.c_str(), 15, 10, 30, RED);
    }

    // Draw roads as edges first
    for (Road* road : Town::Instance()->getRoads()) {
        this->drawRoad(road);
    }

    // Draw buildings as nodes second
    for (Building* building : Town::Instance()->getBuildings()) {
        this->drawBuilding(building);
    }

    // End drawing context
    EndDrawing();
}

// 'Game Loop' function, will run every frame until terminated
void Renderer::mainloop() {
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {

        // Move the world position based on mouse movement
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 currentPos = GetMousePosition();
            if (this->mouseDown) {
                this->worldPosition += currentPos - lastMousePos;
            } else {
                this->mouseDown = true;
            }
            this->lastMousePos = currentPos;
        } else {
            this->mouseDown = false;
        }

        // Time in seconds since last frame
        float dt = GetFrameTime();

        // Update town simulation
        Town::Instance()->update(this, dt);

        // Render town
        this->render(dt);
    }
}