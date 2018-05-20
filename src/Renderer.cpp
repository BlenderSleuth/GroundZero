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

#include "Town.h"
#include "Utils.h"
#include "Renderer.h"

// Setup the renderer
Renderer::Renderer() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(0, 0, (void*)"Ground Zero");
    width = GetScreenWidth();
    height = GetScreenHeight();
    ToggleFullscreen();

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
    // DrawText(std::to_string(building->capacity).c_str(), 
    //     position.x+10, position.y+25, fontSize, fontColour);
    
    // DrawText(std::to_string(building->defensibility).c_str(), 
    //     position.x+10, position.y+40, fontSize, fontColour);
    
    // DrawText(std::to_string(building->resources).c_str(), 
    //     position.x+10, position.y+55, fontSize, fontColour);

    const char* numPeople = std::to_string(building->numPeople).c_str();
    const char* numZombies = std::to_string(building->numZombies).c_str();
    fontSize = 36;
    DrawText(numPeople, building->position.x-20, building->position.y, fontSize, BLACK);
    DrawText(numZombies, building->position.x+10, building->position.y, fontSize, RED);
}

// RENDER TOWN, run every frame
void Renderer::render(float deltaTime) {
    // Start drawing context
    BeginDrawing();
    // Clear the last frame
    ClearBackground(backgroundColour);

    // Everything in here is affected by the camera properties
    Begin2dMode(camera);
        // Draw roads as edges first
        for (Road* road : Town::Instance()->getRoads()) {
            drawRoad(road);
        }

        // Draw people moving
        for (Move& m : moves) {
            if (m.zombie) {
               DrawCircleV(m.pos, 10, RED); 
            } else {
                DrawCircleV(m.pos, 10, GREEN);
            }
        }

        // Draw buildings as nodes second
        for (Building* building : Town::Instance()->getBuildings()) {
            drawBuilding(building);
        }

        // Draw mouse
        DrawCircleV(mouse, 10.0f/camera.zoom, RAYWHITE);
    End2dMode();

    // Display HUD
    int fontSize = 36;
    // Time
    const char* time = ("TIME: " + std::to_string(Town::Instance()->time)).c_str();
    DrawText(time, width - 160, 15, fontSize, GREEN);

    // Phase
    const char* phase;
    switch (Town::Instance()->phase) {
    case ZombieMove:
        phase = " Zombie Move";
        break;
    case ZombieInfect:
        phase = "Zombie Infect";
        break;
    case PeopleMove:
        phase = " People Move";
        break;
    }
    DrawText(phase, width - 250, 45, fontSize, GREEN);

    // If show FPS is on, draw the FPS
    if (showFPS) {
        int fps = 0; // deltaTime is in seconds
        if (deltaTime > 0)
            fps = (1.0/deltaTime + 0.5); // Round to nearest FPS rather than truncate
        // Draw in top left corner in red text
        std::string text = std::to_string(fps) + " FPS";
        DrawText(text.c_str(), 10, 15, 30, RED);
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
                Vector2 delta = currentPos - lastMousePos;
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
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Update moves
        std::vector<Move> newMoves;
        for (int i = 0; i < moves.size(); i++) {
            Vector2 delta = (moves[i].end-moves[i].start);
            delta /= (float)timestep;
            moves[i].pos += delta;
            moves[i].frame++;
            if (moves[i].frame != timestep) {
                newMoves.push_back(moves[i]);
            }
        }
        moves = newMoves;

        if (IsKeyDown(KEY_F)) {
            ToggleFullscreen();
        }

        // Time in seconds since last frame
        float dt = GetFrameTime();

        // Update town simulation
        Town::Instance()->update(this, dt);

        // Render town
        render(dt);
    }
}

void Renderer::moveEntityBetween(Building* b1, Building* b2, bool zombie) {
    Move m;
    m.pos = m.start = b1->position;
    m.end = b2->position;
    m.frame = 0;
    m.zombie = zombie;
    moves.push_back(m);
}
