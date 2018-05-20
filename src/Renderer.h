/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include "Building.h"
#include "Road.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void mainloop();

    float width = 0;
    float height = 0;
    Vector2 centre;
    Vector2 mouse;

    bool showFPS = true;

    Color backgroundColour = BLACK;

    Camera2D camera;

    bool mouseDown = false;
    Vector2 lastMousePos = {0, 0};


private:
    void render(float deltaTime);

    void drawRoad(Road* road);
    void drawBuilding(Building* building);
};

#endif // __RENDERER_H_INCLUDED__
