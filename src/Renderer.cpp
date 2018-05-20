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
#include <GLFW/glfw3.h>
#include <raylib.h>
#include <raymath.h>

#include "Town.h"
#include "Utils.h"
#include "Renderer.h"

// Setup the renderer
Renderer::Renderer() {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(0, 0, (void*)"Ground Zero");
    width = GetScreenWidth();
    height = GetScreenHeight();

    SetWindowMinSize(1024, 768);

    Image icon = LoadImage("assets/icon.png");   
    SetWindowIcon(icon);
    
    SetTargetFPS(60);
    HideCursor();

    this->centre = (Vector2){width/2, height/2};

    camera.offset = -Town::Instance()->townCentre + this->centre;
    camera.target = Town::Instance()->townCentre;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}
// Destroy the renderer
Renderer::~Renderer() {  
    CloseWindow();        // Close window and OpenGL context
}

void Renderer::drawRoad(Road* road) {
    // Get start and end position of road - Positions of buildings that it connects to:
    Vector2 start = road->building1->position;
    Vector2 end = road->building2->position;

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
    ClearBackground(backgroundColour);

    Begin2dMode(camera);
    // Draw roads as edges first
    for (Road* road : Town::Instance()->getRoads()) {
        drawRoad(road);
    }

    // Draw buildings as nodes second
    for (Building* building : Town::Instance()->getBuildings()) {
        drawBuilding(building);
    }
    DrawCircleV(mouse, 10.0f/camera.zoom, RED);

    End2dMode();

    // If show FPS is on, draw the FPS
    if (showFPS) {
        int fps = 0; // deltaTime is in seconds
        if (deltaTime > 0)
            fps = (1.0/deltaTime + 0.5); // Round to nearest FPS rather than truncate
        // Draw in top left corner in red text
        std::string text = std::to_string(fps) + " FPS";
        DrawText(text.c_str(), 30, 70, 30, RED);
    }
    
    // End drawing context
    EndDrawing();
}

// 'Game Loop' function, will run every frame until terminated
void Renderer::mainloop() {
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {

        // Highlight buildings when mouse over
        Vector2 currentPos = GetMousePosition();
        mouse = currentPos - camera.offset;

        // Move the world position based on mouse movement
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { 
            if (mouseDown) {
                Vector2 delta = (currentPos - lastMousePos)/camera.zoom;
                camera.offset += delta;
                camera.target -= delta;
            } else {
                mouseDown = true;
            }
            lastMousePos = currentPos;
        } else {
            mouseDown = false;
        }

        // Check building rectangles
        for (Building* building : Town::Instance()->getBuildings()) {
            if (CheckCollisionPointRec(currentPos - camera.offset, building->boundingBox())) {
                building->highlight();
            } else {
                building->dehighlight();
            }
        }

        // Camera zoom controls
        camera.zoom += ((float)GetMouseWheelMove()*0.5f);
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.5f) camera.zoom = 0.5f;

        // Time in seconds since last frame
        float dt = GetFrameTime();

        // Update town simulation
        Town::Instance()->update(this, dt);

        // Render town
        render(dt);
    }
}
